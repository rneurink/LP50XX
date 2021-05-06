
#include "LP50XX.h"
#include "I2C_coms.h"

/*----------------------- Initialisation functions --------------------------*/

/**
 * @brief This function instantiates the class object
 */
LP50XX::LP50XX() {

}

/**
 * @brief This function instantiates the class object with an enable pin
 * 
 * @param enable_pin 
 */
LP50XX::LP50XX(uint8_t enable_pin) {
    LP50XX();

    pinMode(enable_pin, OUTPUT);
    _enable_pin = enable_pin;
}

/**
 * @brief 
 * 
 * @param i2cAddress 
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

void LP50XX::ResetRegisters() {
    i2c_write_byte(_i2c_address, RESET_REGISTERS, 0xFF);
}


/*----------------------- Configuration functions ---------------------------*/

void LP50XX::Configure(uint8_t configuration) {
    i2c_write_byte(_i2c_address, DEVICE_CONFIG1, configuration & 0x3F);
}

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


/*----------------------- Bank control functions ----------------------------*/

/**
 * @brief 
 * 
 * @param leds 
 */
void LP50XX::SetBankControl(uint8_t leds) {
    i2c_write_byte(_i2c_address, LED_CONFIG0, leds);
}

/**
 * @brief 
 * 
 * @param brightness 
 */
void LP50XX::SetBankBrightness(uint8_t brightness) {
    i2c_write_byte(_i2c_address, BANK_BRIGHTNESS, brightness);
}

void LP50XX::SetBankColorA(uint8_t value) {
    i2c_write_byte(_i2c_address, BANK_A_COLOR, value);
}

void LP50XX::SetBankColorB(uint8_t value) {
    i2c_write_byte(_i2c_address, BANK_B_COLOR, value);
}

void LP50XX::SetBankColorC(uint8_t value) {
    i2c_write_byte(_i2c_address, BANK_C_COLOR, value);
}


/*----------------------- Output control functions --------------------------*/

void LP50XX::SetLEDBrightness(uint8_t led, uint8_t brighness) {
    i2c_write_byte(_i2c_address, LED0_BRIGHTNESS + led, brighness);
}

void LP50XX::SetOutputColor(uint8_t output, uint8_t value) {
    i2c_write_byte(_i2c_address, OUT0_COLOR + output, value);
}



void LP50XX::Test() {
    uint8_t buffer[3];
    buffer[2] = 0x40;
    buffer[1] = 0x00;
    buffer[0] = 0xff;
    i2c_write_multi(_i2c_address, OUT6_COLOR, buffer, 3);
}