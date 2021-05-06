#include "LP50XX.h"

#define ENABLE_PIN 2
LP50XX device(RGB, ENABLE_PIN);
//LP50XX device;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  // Support for 400kHz available
  Wire.setClock(400000UL);

  device.Begin();

  device.Configure(LED_GLOBAL_OFF | MAX_CURRENT_35mA | AUTO_INC_OFF | PWM_DITHERING_OFF | POWER_SAVE_OFF | LOG_SCALE_OFF);
  uint8_t buffer;
  device.ReadRegister(DEVICE_CONFIG1, &buffer);
  Serial.println("Config: " + String(buffer, HEX));

  device.SetScaling(LOG_SCALE_ON);
  device.SetPowerSaving(POWER_SAVE_ON);
  device.SetAutoIncrement(AUTO_INC_ON);
  device.SetPWMDithering(PWM_DITHERING_ON);
  device.SetMaxCurrentOption(MAX_CURRENT_25mA);
  device.SetGlobalLedOff(LED_GLOBAL_ON);

  device.ReadRegister(DEVICE_CONFIG1, &buffer);
  Serial.println("Config: " + String(buffer, HEX));

  device.SetBankControl(LED_0 | LED_1);
  device.SetBankColorA(0x7f);
  device.SetBankColorB(0x20);

  device.SetOutputColor(11, 0x40);

  delay(1000);

  device.Reset();

  delay(10);

  device.SetBankControl(LED_0 | LED_1);
  device.SetBankColor(0x00, 0x40, 0xff);

  device.SetLEDColor(3, 0x40, 0x00, 0x00);
  device.SetLEDColor(2, 0xff, 0x00, 0x7f);
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
