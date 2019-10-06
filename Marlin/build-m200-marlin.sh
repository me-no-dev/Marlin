#!/bin/bash
MARLIN_DIR=$HOME/Documents/Arduino/Marlin

ARDUINO_HOME=$HOME/Documents/Arduino
ARDUINO_IDE=/Applications/Arduino.app/Contents/Java
ARDUINO_PKG=$HOME/Library/Arduino15/packages

PLATFORM_TOOLS=$ARDUINO_PKG/STM32/tools
BOARD_FQBN=STM32:stm32:3dprinter:pnum=MALYANM200_F070CB,upload_method=swdMethod,xserial=generic,usb=CDC,xusb=FS,opt=osstd,rtlib=nanofp
STMTOOLS_VERSION=1.3.0
CMSIS_VERSION=5.5.1
TOOLCHAIN_VERSION=8.2.1-1.7

BUILD_DIR=$HOME/.tmp/arduino_build
CACHE_DIR=$HOME/.tmp/arduino_cache

OUT_DIR="/Volumes/NO NAME"
if [ ! -d "$OUT_DIR" ]; then
    OUT_DIR=$PWD
fi

rm -rf "$OUT_DIR/firmware.bin" "$OUT_DIR/fcupdate.flg" && \
mkdir -p $BUILD_DIR && rm -rf $BUILD_DIR/* && \
mkdir -p $CACHE_DIR && \
/Applications/Arduino.app/Contents/Java/arduino-builder \
    -compile \
    -logger=human \
    -hardware $ARDUINO_IDE/hardware \
    -hardware $ARDUINO_PKG \
    -hardware $ARDUINO_HOME/hardware \
    -tools $ARDUINO_IDE/tools-builder \
    -tools $ARDUINO_IDE/hardware/tools/avr \
    -tools $ARDUINO_PKG \
    -built-in-libraries $ARDUINO_IDE/libraries \
    -libraries $ARDUINO_HOME/libraries \
    -fqbn=$BOARD_FQBN \
    -vid-pid=2974_0503 \
    -ide-version=10810 \
    -build-path $BUILD_DIR \
    -warnings=default \
    -build-cache $CACHE_DIR \
    -prefs=build.warn_data_percentage=75 \
    -prefs=runtime.tools.STM32Tools.path=$PLATFORM_TOOLS/STM32Tools/$STMTOOLS_VERSION \
    -prefs=runtime.tools.STM32Tools-$STMTOOLS_VERSION.path=$PLATFORM_TOOLS/STM32Tools/$STMTOOLS_VERSION \
    -prefs=runtime.tools.CMSIS.path=$PLATFORM_TOOLS/CMSIS/$CMSIS_VERSION \
    -prefs=runtime.tools.CMSIS-$CMSIS_VERSION.path=$PLATFORM_TOOLS/CMSIS/$CMSIS_VERSION \
    -prefs=runtime.tools.arm-none-eabi-gcc.path=$PLATFORM_TOOLS/arm-none-eabi-gcc/$TOOLCHAIN_VERSION \
    -prefs=runtime.tools.arm-none-eabi-gcc-$TOOLCHAIN_VERSION.path=$PLATFORM_TOOLS/arm-none-eabi-gcc/$TOOLCHAIN_VERSION \
    -verbose \
    $MARLIN_DIR/Marlin/Marlin.ino && \
    cp $BUILD_DIR/Marlin.ino.bin "$OUT_DIR/firmware.bin" && \
    touch "$OUT_DIR/fcupdate.flg"
