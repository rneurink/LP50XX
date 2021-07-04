/**
 * This example contains a simple application to rainbow cycle the RGB colors of LED 0 output0..2 of the LP5009/LP5012
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
}

void loop() {
  // put your main code here, to run repeatedly:

  device.SetLEDColor(0, 255, 0, 0); // Full red on output 0
  delay(1000);
  device.SetLEDColor(0, 0, 255, 0); // Full green on output 0
  delay(1000);
  device.SetLEDColor(0, 0, 0, 255); // Full blue on output 0
  delay(1000);

  for (int i = 0; i <= 255; i++) {
    Rainbow(0, i);
    delay(10);
  }
}

void Rainbow(uint8_t output, uint8_t rainbowPos) {
  rainbowPos = 255 - rainbowPos;
  if (rainbowPos < 85) {
    device.SetLEDColor(output, 255 - rainbowPos * 3, 0, rainbowPos * 3);
    return;
  }
  if (rainbowPos < 170) {
    rainbowPos -= 85;
    device.SetLEDColor(output, 0, rainbowPos * 3, 255 - rainbowPos * 3);
    return;
  }
  rainbowPos -= 170;
  device.SetLEDColor(output, rainbowPos * 3, 255 - rainbowPos * 3, 0);
}