
#include "LP50XX.h"

/**
 * @brief This function instantiates the class object
 */
LP50XX::LP50XX() {
    
}

/**
 * @brief 
 */
void VL53L1X_ULD::Begin(uint8_t i2cAddress) {
    _i2c_address = i2cAddress;
}
