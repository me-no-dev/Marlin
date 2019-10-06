#!/bin/bash
MARLIN_DIR=$HOME/Documents/Arduino/Marlin
ARDUINO_HOME=$HOME/Documents/Arduino
ARDUINO_IDE=/Applications/Arduino.app/Contents/Java

BOARD_FQBN=STM32:stm32:3dprinter:pnum=MALYANM200_F070CB,upload_method=swdMethod,xserial=generic,usb=CDC,xusb=FS,opt=osstd,rtlib=nanofp

BUILD_DIR=$HOME/.tmp/arduino_build
CACHE_DIR=$HOME/.tmp/arduino_cache

OUT_DIR="/Volumes/NO NAME"
if [ ! -d "$OUT_DIR" ]; then
    OUT_DIR=$PWD
fi

rm -rf "$OUT_DIR/firmware.bin" "$OUT_DIR/fcupdate.flg" && \
mkdir -p $BUILD_DIR && rm -rf $BUILD_DIR/* && \
mkdir -p $CACHE_DIR && \
$ARDUINO_IDE/arduino-builder \
    -compile \
    -logger=human \
    -tools $ARDUINO_IDE/tools-builder \
    -built-in-libraries $ARDUINO_IDE/libraries \
    -hardware $ARDUINO_HOME/hardware \
    -libraries $ARDUINO_HOME/libraries \
    -build-path $BUILD_DIR \
    -build-cache $CACHE_DIR \
    -fqbn=$BOARD_FQBN \
    -vid-pid=2974_0503 \
    -ide-version=10810 \
    -warnings=default \
    -prefs=build.warn_data_percentage=75 \
    $MARLIN_DIR/Marlin/Marlin.ino && \
    cp $BUILD_DIR/Marlin.ino.bin "$OUT_DIR/firmware.bin" && \
    touch "$OUT_DIR/fcupdate.flg"
