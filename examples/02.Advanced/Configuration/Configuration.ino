/**
 * This example contains a simple application configure the LP5009/LP5012
 */

#include "LP50XX.h"

#define ENABLE_PIN 2
LP50XX device(ENABLE_PIN);

// Use this if you don't have an enable pin
// LP50XX device;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  // Support for 400kHz available
  Wire.setClock(400000UL);

  device.Begin();

  // Configration can be done in one line or with multiple calls
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
}

void loop() {
  
}
