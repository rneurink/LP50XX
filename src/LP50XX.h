#ifndef __LP50XX_H
#define __LP50XX_H

#include <Arduino.h>
#include <Wire.h>

#define DEFAULT_ADDRESS 0x14
#define BROADCAST_ADDRESS 0x0C

enum LED_Configuration {
    RGB,
    GRB,
    BGR,
    RBG,
    GBR,
    BRG,
};

enum LP50XX_LEDS {
    LED_0 = 1,
    LED_1 = 2,
    LED_2 = 4,
    LED_3 = 8
};

enum LP50XX_Configuration {
    LED_GLOBAL_ON = 0 << 0,
    LED_GLOBAL_OFF = 1 << 0,
    MAX_CURRENT_25mA = 0 << 1,
    MAX_CURRENT_35mA = 1 << 1,
    PWM_DITHERING_OFF = 0 << 2,
    PWM_DITHERING_ON = 1 << 2,
    AUTO_INC_OFF = 0 << 3,
    AUTO_INC_ON = 1 << 3,
    POWER_SAVE_OFF = 0 << 4,
    POWER_SAVE_ON = 1 << 4,
    LOG_SCALE_OFF = 0 << 5,
    LOG_SCALE_ON = 1 << 5
};

// Register definitions
#define DEVICE_CONFIG0 0x00     // Chip_EN
#define DEVICE_CONFIG1 0x01     // Configurations for Log_scale, Power_save, Auto_inc, PWM_dithering, Max_current_option and LED_Global_off
#define LED_CONFIG0 0x02        // Contains the BANK configurations
#define BANK_BRIGHTNESS 0x03    // Contains the BANK brightness level 
#define BANK_A_COLOR 0x04       // Contains the BANK A color value
#define BANK_B_COLOR 0x05       // Contains the BANK B color value
#define BANK_C_COLOR 0x06       // Contains the BANK C color value
#define LED0_BRIGHTNESS 0x07    // Contains the brightness level for LED 0
#define LED1_BRIGHTNESS 0x08    // Contains the brightness level for LED 1
#define LED2_BRIGHTNESS 0x09    // Contains the brightness level for LED 2
#define LED3_BRIGHTNESS 0x0A    // Contains the brightness level for LED 3 (only on the LP5012)
#define OUT0_COLOR 0x0B         // Contains the color value for output 0
#define OUT1_COLOR 0x0C         // Contains the color value for output 1
#define OUT2_COLOR 0x0D         // Contains the color value for output 2
#define OUT3_COLOR 0x0E         // Contains the color value for output 3
#define OUT4_COLOR 0x0F         // Contains the color value for output 4
#define OUT5_COLOR 0x10         // Contains the color value for output 5
#define OUT6_COLOR 0x11         // Contains the color value for output 6
#define OUT7_COLOR 0x12         // Contains the color value for output 7
#define OUT8_COLOR 0x13         // Contains the color value for output 8
#define OUT9_COLOR 0x14         // Contains the color value for output 9 (only on the LP5012)
#define OUT10_COLOR 0x15        // Contains the color value for output 10 (only on the LP5012)
#define OUT11_COLOR 0x16        // Contains the color value for output 11 (only on the LP5012)
#define RESET_REGISTERS 0x17    // Resets all the registers to their default values

/**
 * @brief Class to communicate with the LP5009 or LP5012
 */
class LP50XX 
{
    public:
        LP50XX(void); // Constructor
        LP50XX(LED_Configuration ledConfiguration); // Constructor with a specific led configuration
        LP50XX(uint8_t enablePin); // Constructor with enable pin
        LP50XX(LED_Configuration ledConfiguration, uint8_t enablePin); // Constructor with a specific led configuration and an enable pin

        /**
         * Initialisation functions
         */
        void Begin(uint8_t i2c_address = DEFAULT_ADDRESS); // Initialize the driver
        void Reset();
        void ResetRegisters();

        /**
         * Configuration functions
         */
        void Configure(uint8_t configuration);
        void SetScaling(uint8_t scaling);
        void SetPowerSaving(uint8_t powerSave);
        void SetAutoIncrement(uint8_t autoInc);
        void SetPWMDithering(uint8_t dithering);
        void SetMaxCurrentOption(uint8_t option);
        void SetGlobalLedOff(uint8_t value);

        void SetEnablePin(uint8_t enablePin);
        void SetLEDConfiguration(LED_Configuration ledConfiguration);
        void SetI2CAddress(uint8_t address);

        /**
         * Bank control functions
         */
        void SetBankControl(uint8_t leds);
        void SetBankBrightness(uint8_t brightness);
        void SetBankColorA(uint8_t value);
        void SetBankColorB(uint8_t value);
        void SetBankColorC(uint8_t value);
        void SetBankColor(uint8_t red, uint8_t green, uint8_t blue);

        /**
         * Output control functions
         */
        void SetLEDBrightness(uint8_t led, uint8_t brighness);
        void SetOutputColor(uint8_t output, uint8_t value);
        void SetLEDColor(uint8_t led, uint8_t red, uint8_t green, uint8_t blue);


        /**
         * Low level functions
         */
        void WriteRegister(uint8_t reg, uint8_t value);
        void ReadRegister(uint8_t reg, uint8_t *value);

    protected:

    private:
        uint8_t     _i2c_address;
        uint8_t     _enable_pin = 0xFF;
        LED_Configuration     _led_configuration = RGB;
};

#endif