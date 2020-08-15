/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#ifdef ARDUINO_ARCH_ESP32

#include "../../inc/MarlinConfig.h"

#if HAS_SERVOS

#include "Servo.h"

int Servo::channel_next_free = 0;

Servo::Servo() {
    this->channel = channel_next_free++;
    this->pin = -1;
    this->degrees = 0;
    this->servo_delay = 0;
    this->rmt = NULL;
    this->pulse.val = 0;
#if ENABLED(DEACTIVATE_SERVOS_AFTER_MOVE)
    for (uint8_t i=0; i<64; i++) {
        this->pulses[i].val = this->pulse.val;
    }
#endif
}

int8_t Servo::attach(const int pin) {
    constexpr uint16_t servo_delays[] = SERVO_DELAY;
    static_assert(COUNT(servo_delays) == NUM_SERVOS, "SERVO_DELAY must be an array NUM_SERVOS long.");
    if (this->channel >= NUM_SERVOS) {
        return -1;
    }
    if (this->pin < 0 && pin >= 0) {
        this->pin = pin;
    }
    if (this->pin < 0) {
        return -1;
    }
    if (this->rmt == NULL) {
        this->servo_delay = servo_delays[this->channel];
        this->rmt = rmtInit(this->pin, true, RMT_MEM_64);
        if (this->rmt == NULL) {
            return -1;
        }
        rmtSetTick(this->rmt, 1000);
    }
    return pin;
}

void Servo::detach() {
    if (this->pin < 0 && this->rmt == NULL) {
        return;
    }
    uint32_t v = 0;
    rmtWrite(this->rmt, (rmt_data_t*)&v, 1);
}

int Servo::read() {
    return this->degrees;
}

void Servo::write(int inDegrees) {
    if (this->pin < 0 && this->rmt == NULL) {
        return;
    }
    this->degrees = constrain(inDegrees, MIN_ANGLE, MAX_ANGLE);
    int us = map(this->degrees, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    if (us != this->pulse.duration0) {
        this->pulse.duration0 = us;
        this->pulse.level0 = 1;
        this->pulse.duration1 = 20000 - us;
        this->pulse.level1 = 0;
#if ENABLED(DEACTIVATE_SERVOS_AFTER_MOVE)
        for (uint8_t i=0; i<64; i++) {
            this->pulses[i].val = this->pulse.val;
        }
#endif
    }
#if ENABLED(DEACTIVATE_SERVOS_AFTER_MOVE)
    rmtWrite(this->rmt, this->pulses, min((this->servo_delay/20), 64));
#else
    rmtLoop(this->rmt, &this->pulse, 1);
#endif
}

void Servo::move(const int value) {
    if (this->pin < 0 && this->rmt == NULL) {
        return;
    }
    this->write(value);
    safe_delay(this->servo_delay);
}
#endif // HAS_SERVOS

#endif // ARDUINO_ARCH_ESP32
