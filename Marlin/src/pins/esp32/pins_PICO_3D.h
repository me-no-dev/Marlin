/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Espressif ESP32 (Tensilica Xtensa LX6) pin assignments
 */

#ifndef ARDUINO_ARCH_ESP32
  "Oops! Select an ESP32 board in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME "ESP32 PICO-3D"

#define TIMER_ISR_ON_CORE   1 //Fix timer ISRs to Core 1

//
// SPI
//
#define SCK_PIN             5
#define MISO_PIN            37
#define MOSI_PIN            18
#define SS_PIN              23
#define SDSS                SS_PIN

//
// Servos
//
#define SERVO0_PIN          0

//
// Steppers
//
#define X_STEP_PIN          4
#define X_DIR_PIN           2
#define X_ENABLE_PIN        15

#define Y_STEP_PIN          13
#define Y_DIR_PIN           12
#define Y_ENABLE_PIN        X_ENABLE_PIN

#define Z_STEP_PIN          14
#define Z_DIR_PIN           27
#define Z_ENABLE_PIN        X_ENABLE_PIN

#define E0_STEP_PIN         33
#define E0_DIR_PIN          32
#define E0_ENABLE_PIN       X_ENABLE_PIN

//
// Limit Switches
//
#define X_MIN_PIN           38
#define Y_MIN_PIN           34
#define Z_MIN_PIN           35

#define ONBOARD_ENDSTOPPULLUPS // Board has built-in pullups

//
// Heaters
//
#define HEATER_0_PIN        25
#define HEATER_BED_PIN      26

//
// Temperature Sensors
//
#define TEMP_0_PIN          36 // Analog Input
#define TEMP_BED_PIN        39 // Analog Input

//
// Fans
//
#define FAN_PIN             21 // Part cooling fan
#define FAN1_PIN            22 // E0_AUTO_FAN (hot end fan)
#define FAN2_PIN            19 // CONTROLLER_FAN (control board fan)

#if HAS_TMC220x
  /**
   * TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * Serial1 for PICO-D4
   */
  #define X_HARDWARE_SERIAL  Serial1
  #define Y_HARDWARE_SERIAL  X_HARDWARE_SERIAL
  #define Z_HARDWARE_SERIAL  X_HARDWARE_SERIAL
  #define E0_HARDWARE_SERIAL X_HARDWARE_SERIAL
#endif
