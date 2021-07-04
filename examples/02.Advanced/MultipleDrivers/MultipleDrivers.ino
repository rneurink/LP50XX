/**
 * This example contains a simple application to pulse output 0 of multiple LP5009/LP5012
 */

#include "LP50XX.h"

#define ENABLE_PIN_1 2
#define ENABLE_PIN_2 3

#define I2C_Address_1 0x14
#define I2C_Address_2 0x15

LP50XX device(ENABLE_PIN_1);
LP50XX device2(ENABLE_PIN_2);

// Use this if you don't have an enable pin
// LP50XX device;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  // Support for 400kHz available
  Wire.setClock(400000UL);

  device.Begin(I2C_Address_1);
  device2.Begin(I2C_Address_2);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 255; i++) {
    device.SetOutputColor(0, i);
    device2.SetOutputColor(0, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    device.SetOutputColor(0, i);
    device2.SetOutputColor(0, i);
    delay(10);
  }
}