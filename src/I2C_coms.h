/**
 * @file  I2C_coms.h
 * @brief Contains i2c implementation of the platform
 */
 
#ifndef _I2C_COMS_H_
#define _I2C_COMS_H_

#include "Arduino.h"
#include "Wire.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief i2c_init() definition.\n
 * 
 */
int8_t i2c_init();

/** @brief i2c_write_multi() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_multi(
        uint8_t       deviceAddress,
        uint8_t       registerAddress,
        uint8_t      *pdata,
        uint32_t      count);
/** @brief i2c_read_multi() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_multi(
        uint8_t       deviceAddress,
        uint8_t       registerAddress,
        uint8_t      *pdata,
        uint32_t      count);
/** @brief i2c_write_byte() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_write_byte(
        uint8_t       deviceAddress,
        uint8_t       registerAddress,
        uint8_t       data);
// /** @brief i2c_write_word() definition.\n
//  * To be implemented by the developer
//  */
// int8_t i2c_write_word(
//         uint8_t       deviceAddress,
//         uint8_t       registerAddress,
//         uint16_t      data);
// /** @brief i2c_write_Dword() definition.\n
//  * To be implemented by the developer
//  */
// int8_t i2c_write_Dword(
//         uint8_t       deviceAddress,
//         uint8_t      registerAddress,
//         uint32_t      data);
/** @brief i2c_read_byte() definition.\n
 * To be implemented by the developer
 */
int8_t i2c_read_byte(
        uint8_t       deviceAddress,
        uint8_t       registerAddress,
        uint8_t      *pdata);
// /** @brief i2c_read_word() definition.\n
//  * To be implemented by the developer
//  */
// int8_t i2c_read_word(
//         uint8_t       deviceAddress,
//         uint8_t       registerAddress,
//         uint16_t     *pdata);
// /** @brief i2c_read_Dword() definition.\n
//  * To be implemented by the developer
//  */
// int8_t i2c_read_Dword(
//         uint8_t       deviceAddress,
//         uint8_t       registerAddress,
//         uint32_t     *pdata);

#ifdef __cplusplus
}
#endif

#endif
