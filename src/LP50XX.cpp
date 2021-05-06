
#include "LP50XX.h"
#include "I2C_coms.h"

/*----------------------- Initialisation functions --------------------------*/

/**
 * @brief This function instantiates the class object
 */
LP50XX::LP50XX() {

}

/**
 * @brief This function instantiates the class object with a specific LED configuration
 * 
 * @param ledConfiguration The LED configuration in which the leds are attached to the outputs. See @ref LED_Configuration
 */
LP50XX::LP50XX(LED_Configuration ledConfiguration) {
    _led_configuration = ledConfiguration;

    LP50XX();
}

/**
 * @brief This function instantiates the class object with an enable pin
 * 
 * @param enablePin the pin that is connected to the EN pin of the LP5009 or LP5012
 */
LP50XX::LP50XX(uint8_t enablePin) {
    pinMode(enablePin, OUTPUT);
    _enable_pin = enablePin;

    LP50XX();
}

/**
 * @brief This function instantiates the class object with a specific LED configuration and with an enable pin
 * 
 * @param ledConfiguration The LED configuration in which the leds are attached to the outputs. See @ref LED_Configuration
 * @param enablePin the pin that is connected to the EN pin of the LP5009 or LP5012
 */
LP50XX::LP50XX(LED_Configuration ledConfiguration, uint8_t enablePin) {
    _led_configuration = ledConfiguration;
    
    pinMode(enablePin, OUTPUT);
    _enable_pin = enablePin;

    LP50XX();
}

/**
 * @brief Initializes the I2C bus and the LP5009 or LP5012
 * 
 * @param i2cAddress The I2C address of the device
 */
void LP50XX::Begin(uint8_t i2cAddress) {
    i2c_init();
    _i2c_address = i2cAddress;

    if (_enable_pin != 0xFF) {
        digitalWrite(_enable_pin, HIGH);
    }

    // 500 us delay after enabling the device before I2C access is available
    delayMicroseconds(500);

    // Enable the Chip_EN bit to start up the device
    i2c_write_byte(_i2c_address, DEVICE_CONFIG0, 1 << 6);
}

/**
 * @brief Resets the device by using the enable pin if available and resetting the registers
 * 
 */
void LP50XX::Reset() {
    if (_enable_pin != 0xFF) {
        digitalWrite(_enable_pin, LOW);
        delay(10);
        digitalWrite(_enable_pin, HIGH);
        // 500 us delay after enabling the device before I2C access is available
        delayMicroseconds(500);
    }
    
    ResetRegisters();

    // Enable the Chip_EN bit to start up the device
    i2c_write_byte(_i2c_address, DEVICE_CONFIG0, 1 << 6);
}

/**
 * @brief Resets the registers to their original values
 * 
 */
void LP50XX::ResetRegisters() {
    i2c_write_byte(_i2c_address, RESET_REGISTERS, 0xFF);
}


/*----------------------- Configuration functions ---------------------------*/

/**
 * @brief Configures the device according to the configuration param
 * 
 * @param configuration The configuration of the device, this can be made by bitwise OR ('|') the enum @ref LP50XX_Configuration
 * 
 * @note A configuration can be `Configure(LED_GLOBAL_ON | MAX_CURRENT_25mA | PWM_DITHERING_ON | AUTO_INC_ON | POWER_SAVE_ON | LOG_SCALE_ON);`
 */
void LP50XX::Configure(uint8_t configuration) {
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, configuration & 0x3F);
}

/**
 * @brief Sets the PWM scaling used by the device
 * 
 * @param scaling The scaling of the device. @ref LOG_SCALE_OFF @ref LOG_SCALE_ON
 */
void LP50XX::SetScaling(uint8_t scaling) {
    uint8_t buff;
    i2c_read_byte(_i2c_address, DEVICE_CONFIG1, &buff);

    scaling = scaling & 1 << 5;
    if (scaling >> 5 & 1) {
        buff |= 1 << 5;
    } else {
        buff &= ~(1 << 5);
    }
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, buff);
}

/**
 * @brief Sets the power saving mode of the device
 * 
 * @param powerSave The power saving mode. @ref POWER_SAVE_OFF @ref POWER_SAVE_ON
 */
void LP50XX::SetPowerSaving(uint8_t powerSave) {
    uint8_t buff;
    i2c_read_byte(_i2c_address, DEVICE_CONFIG1, &buff);

    powerSave = powerSave & 1 << 4;
    if (powerSave >> 4 & 1) {
        buff |= 1 << 4;
    } else {
        buff &= ~(1 << 4);
    }
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, buff);
}

/**
 * @brief Sets the auto increment mode of the device
 * 
 * @param autoInc The auto increment mode. @ref AUTO_INC_OFF @ref AUTO_INC_ON
 */
void LP50XX::SetAutoIncrement(uint8_t autoInc) {
    uint8_t buff;
    i2c_read_byte(_i2c_address, DEVICE_CONFIG1, &buff);

    autoInc = autoInc & 1 << 3;
    if (autoInc >> 3 & 1) {
        buff |= 1 << 3;
    } else {
        buff &= ~(1 << 3);
    }
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, buff);
}

/**
 * @brief Sets the PWM dithering of the device
 * 
 * @param dithering The dithering mode. @ref PWM_DITHERING_OFF @ref PWM_DITHERING_ON
 */
void LP50XX::SetPWMDithering(uint8_t dithering) {
    uint8_t buff;
    i2c_read_byte(_i2c_address, DEVICE_CONFIG1, &buff);

    dithering = dithering & 1 << 2;
    if (dithering >> 2 & 1) {
        buff |= 1 << 2;
    } else {
        buff &= ~(1 << 2);
    }
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, buff);
}

/**
 * @brief Sets the max current option of the device
 * 
 * @param option The max current option. @ref MAX_CURRENT_25mA @ref MAX_CURRENT_35mA
 */
void LP50XX::SetMaxCurrentOption(uint8_t option) {
    uint8_t buff;
    i2c_read_byte(_i2c_address, DEVICE_CONFIG1, &buff);

    option = option & 1 << 1;
    if (option >> 1 & 1) {
        buff |= 1 << 1;
    } else {
        buff &= ~(1 << 1);
    }
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, buff);
}

/**
 * @brief Turns all LED outputs ON or OFF
 * 
 * @param value The desired setting. @ref LED_GLOBAL_OFF @ref LED_GLOBAL_ON
 */
void LP50XX::SetGlobalLedOff(uint8_t value) {
    uint8_t buff;
    i2c_read_byte(_i2c_address, DEVICE_CONFIG1, &buff);

    value = value & 1 << 0;
    if (value >> 0 & 1) {
        buff |= 1 << 0;
    } else {
        buff &= ~(1 << 0);
    }
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, buff);
}


/**
 * @brief Sets the enable pin of the device. This pin is used to enable the device in @ref Begin
 * 
 * @param enablePin 
 */
void LP50XX::SetEnablePin(uint8_t enablePin) {
    pinMode(enablePin, OUTPUT);
    _enable_pin = enablePin;
}

/**
 * @brief Sets the LED configuration acording the @ref LED_Configuration enum
 * 
 * @param ledConfiguration 
 */
void LP50XX::SetLEDConfiguration(LED_Configuration ledConfiguration) {
    _led_configuration = ledConfiguration;
}

/**
 * @brief Sets the I2C address
 * 
 * @param address 
 */
void LP50XX::SetI2CAddress(uint8_t address) {
    _i2c_address = address;
}


/*----------------------- Bank control functions ----------------------------*/

/**
 * @brief Enables or Disables BANK control for specific LEDs
 * 
 * @param leds The LEDs to include in BANK control. See @ref LP50XX_LEDS
 * 
 * @note Code example could be `SetBankControl(LED_0 | LED_1 | LED_2 | LED_3);`
 */
void LP50XX::SetBankControl(uint8_t leds) {
    i2c_write_byte(_i2c_address, LED_CONFIG0, leds);
}

/**
 * @brief Sets the brightness level of the whole BANK
 * 
 * @param brightness The brightness level from 0 to 0xFF
 */
void LP50XX::SetBankBrightness(uint8_t brightness) {
    i2c_write_byte(_i2c_address, BANK_BRIGHTNESS, brightness);
}

/**
 * @brief Sets BANK color A related to Output 0,3,6,9
 * 
 * @param value The color value from 0 to 0xFF
 */
void LP50XX::SetBankColorA(uint8_t value) {
    i2c_write_byte(_i2c_address, BANK_A_COLOR, value);
}

/**
 * @brief Sets BANK color B related to Output 1,4,7,10
 * 
 * @param value The color value from 0 to 0xFF
 */
void LP50XX::SetBankColorB(uint8_t value) {
    i2c_write_byte(_i2c_address, BANK_B_COLOR, value);
}

/**
 * @brief Sets BANK color C related to Output 2,5,8,11
 * 
 * @param value The color value from 0 to 0xFF
 */
void LP50XX::SetBankColorC(uint8_t value) {
    i2c_write_byte(_i2c_address, BANK_C_COLOR, value);
}

/**
 * @brief Sets the BANK color according to the set LED configuration @ref SetLEDConfiguration
 * 
 * @param red The red color value from 0 to 0xFF
 * @param green The green color value from 0 to 0xFF
 * @param blue The blue color value from 0 to 0xFF
 */
void LP50XX::SetBankColor(uint8_t red, uint8_t green, uint8_t blue) {
    SetAutoIncrement(AUTO_INC_ON);

    uint8_t buff[3];
    switch (_led_configuration)
    {
    case RGB:
        buff[0] = red;
        buff[1] = green;
        buff[2] = blue;
        break;
    case GRB:
        buff[0] = green;
        buff[1] = red;
        buff[2] = blue;
        break;
    case BGR:
        buff[0] = blue;
        buff[1] = green;
        buff[2] = red;
        break;
    case RBG:
        buff[0] = red;
        buff[1] = blue;
        buff[2] = green;
        break;
    case GBR:
        buff[0] = green;
        buff[1] = blue;
        buff[2] = red;
        break;
    case BRG:
        buff[0] = blue;
        buff[1] = red;
        buff[2] = green;
        break;
    }

    i2c_write_multi(_i2c_address, BANK_A_COLOR, buff, 3);
}


/*----------------------- Output control functions --------------------------*/

/**
 * @brief Sets the brightness level of a single LED (3 outputs)
 * 
 * @param led The led to set. 0..3
 * @param brighness The brightness level from 0 to 0xFF
 */
void LP50XX::SetLEDBrightness(uint8_t led, uint8_t brighness) {
    i2c_write_byte(_i2c_address, LED0_BRIGHTNESS + led, brighness);
}

/**
 * @brief Sets the color level of a single output
 * 
 * @param output The output to set. 0..11
 * @param value The color value from 0 to 0xFF
 */
void LP50XX::SetOutputColor(uint8_t output, uint8_t value) {
    i2c_write_byte(_i2c_address, OUT0_COLOR + output, value);
}

/**
 * @brief Sets the LED color according to the set LED configuration @ref SetLEDConfiguration
 * 
 * @param led The led to set. 0..3
 * @param red The red color value from 0 to 0xFF
 * @param green The green color value from 0 to 0xFF
 * @param blue The blue color value from 0 to 0xFF
 */
void LP50XX::SetLEDColor(uint8_t led, uint8_t red, uint8_t green, uint8_t blue) {
    SetAutoIncrement(AUTO_INC_ON);

    uint8_t buff[3];
    switch (_led_configuration)
    {
    case RGB:
        buff[0] = red;
        buff[1] = green;
        buff[2] = blue;
        break;
    case GRB:
        buff[0] = green;
        buff[1] = red;
        buff[2] = blue;
        break;
    case BGR:
        buff[0] = blue;
        buff[1] = green;
        buff[2] = red;
        break;
    case RBG:
        buff[0] = red;
        buff[1] = blue;
        buff[2] = green;
        break;
    case GBR:
        buff[0] = green;
        buff[1] = blue;
        buff[2] = red;
        break;
    case BRG:
        buff[0] = blue;
        buff[1] = red;
        buff[2] = green;
        break;
    }

    i2c_write_multi(_i2c_address, OUT0_COLOR + (led * 3), buff, 3);
}


/*----------------------- Low level functions -------------------------------*/

/**
 * @brief Writes a value to a specified register. @warning only use if you know what you're doing
 * 
 * @param reg The register to write to
 * @param value The value to write to the register
 */
void LP50XX::WriteRegister(uint8_t reg, uint8_t value) {
    i2c_write_byte(_i2c_address, reg, value);
}

/**
 * @brief Reads a value from a specified register.
 * 
 * @param reg The register to read from
 * @param value a reference to a @ref uint8_t value
 */
void LP50XX::ReadRegister(uint8_t reg, uint8_t *value) {
    i2c_read_byte(_i2c_address, reg, value);
}