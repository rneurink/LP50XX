#include "LP50XX.h"

#define ENABLE_PIN 2
LP50XX device(ENABLE_PIN);
//LP50XX device;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  // Support for 400kHz available
  Wire.setClock(400000UL);

  device.Begin();

  device.Configure(LED_GLOBAL_ON | MAX_CURRENT_25mA | AUTO_INC_ON | PWM_DITHERING_ON | POWER_SAVE_OFF | LOG_SCALE_OFF);

  device.SetScaling(LOG_SCALE_ON);

  device.SetBankControl(LED_0 | LED_1);
  device.SetBankColorA(0x7f);
  device.SetBankColorB(0x20);

  device.SetOutputColor(11, 0x40);

  delay(1000);

  device.Reset();

  delay(10);

  device.SetBankControl(LED_0 | LED_1);
  device.SetBankColorB(0x7f);
  device.SetBankColorC(0x7f);

  device.SetOutputColor(9, 0x40);

  device.Test();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 0xff; i+= 5) {
    device.SetBankBrightness(i);
    device.SetLEDBrightness(3, ~i);
    delay(10);
  }
  for (int i = 0xff; i > 0; i-= 5) {
    device.SetBankBrightness(i);
    device.SetLEDBrightness(3, ~i);
    delay(10);
  }
}
