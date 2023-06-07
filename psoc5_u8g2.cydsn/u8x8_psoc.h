#ifndef U8X8_PSOC_H_
#define U8X8_PSOC_H_

#include <u8g2.h>
#include <stdint.h>

// change I2COLED to a valid name of YOUR i2c device.
#define DISPLAY_ADDRESS 0x3C
#define I2CDEV(NAME) I2COLED_ ## NAME
    
uint8_t u8x8_byte_psoc_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_psoc_delay(u8x8_t * u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif /* U8X8_PSOC_H_ */
