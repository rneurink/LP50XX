/**
 * This example contains a simple application to dimm the RGB colors of LED 0 output0..2 of the LP5009/LP5012
 */

#include "LP50XX.h"

#define ENABLE_PIN 2
// Initialize driver with an RGB configuration. If you have a different config you can pass GRB, BGR etc into the function
LP50XX device(RGB, ENABLE_PIN);

// Use this if you don't have an enable pin
// LP50XX device(RGB);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  // Support for 400kHz available
  Wire.setClock(400000UL);

  device.Begin();

  device.SetLEDColor(0, 0, 255, 242); // Cyan color on LED 0 
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 255; i++) {
    device.SetLEDBrightness(0, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    device.SetLEDBrightness(0, i);
    delay(10);
  }
}
