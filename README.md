# LP50XX

[![Arduino Lint](https://github.com/rneurink/LP50XX/actions/workflows/arduino-lint.yml/badge.svg?branch=master)](https://github.com/rneurink/LP50XX/actions/workflows/arduino-lint.yml)[![Compile Examples](https://github.com/rneurink/LP50XX/actions/workflows/compile-examples.yml/badge.svg?branch=master)](https://github.com/rneurink/LP50XX/actions/workflows/compile-examples.yml)

## Summary

This is an Arduino library for interaction with the [LP5009](https://www.ti.com/product/LP5009) and [LP5012](https://www.ti.com/product/LP5012) constant current RGB driver from [Texas Instrument](https://www.ti.com/). 

## Supported platforms

This library should be compatible with all Arduino-compatible board packages where an I2C bus is available

### Tested boards/platorms:
- Arduino AVR (Uno, Mega, Nano, Pro Mini, Micro etc.)
- Arduino megaAVR boards (Nano every)
- Adafruit SAMD (SAMD21, SAMD51)
- [MegaCoreX](https://github.com/MCUdude/MegaCoreX) (ATmega4809, ATmega4808, ATmega3209, ATmega3208, ATmega1609, ATmega1608, ATmega809 and ATmega808)
- [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore) (tinyAVR 0-series, tinyAVR 1-series)
- ESP32. The ESP32 needs around 2k2 - 2k7 resistors on the SDA and SCL pins to VCC to work

## Getting started
### Hardware
You can get TSSOP from digikey or mouser and handsolder it to a breakout or PCB.
Currently there are no cheap eval boards available.

Breakout boards:
* [TI LP5012EVM Eval board](https://www.ti.com/tool/LP5012EVM)
* [Xortech LP5012 I2C -> LED PWM](https://www.tindie.com/products/xortech/lp5012-i2c-to-12-led-pwms/)

If more breakout boards are available please inform me to update the list.

### Software
This library is made to work with the Arduino platform and the [Arduino IDE](https://www.arduino.cc/en/software).

1. In the Arduino IDE, open the 'Sketch' menu and select 'Include Library'm then 'Manage Libraries'
2. Search for LP50XX
3. Select the LP50XX entry from the list
4. Click 'Install'

Manual installation:

1. Download the [latest release](https://github.com/rneurink/LP50XX/releases/latest) source code.
2. Unzip the compressed file.
3. Move the LP50XX-VXXX (where VXXX is the Version number) to your libraries folder, which is located in your sketch folder. 
   You can view open your sketch folder location by going to your Arduino IDE and selecting the 'File' menu. After this select the 'Preferences' option and another window will open. In here you can see (and set) your sketchbook location.
4. After the manual installation, restart the Arduino IDE to apply the changes.
