
#include <project.h>
#include "u8x8_psoc.h"
#define I2CDEV(NAME) I2COLED_ ## NAME

uint8_t u8x8_byte_psoc_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    (void) u8x8;
	uint8_t *data;
	switch(msg){
		case U8X8_MSG_BYTE_SEND:
			data = (uint8_t *)arg_ptr;
			while( arg_int-- )
                if (I2CDEV(MSTR_NO_ERROR) != I2CDEV(MasterWriteByte)(*data++)) { return 0; }
			break;
		case U8X8_MSG_BYTE_INIT:
			break;
		case U8X8_MSG_BYTE_SET_DC:
			/* ignored for i2c */
			break;
		case U8X8_MSG_BYTE_START_TRANSFER:
            if ( I2CDEV(MSTR_NO_ERROR) != I2CDEV(MasterSendStart)(u8x8_GetI2CAddress(u8x8),0)) { return 0; }
			break;
		case U8X8_MSG_BYTE_END_TRANSFER:
			I2CDEV(MasterSendStop)();
			break;
		default:
			return 0;
	}
	return 1;
}

uint8_t u8x8_psoc_delay (u8x8_t * u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    (void) u8x8;
    (void) arg_ptr;
    (void) arg_int;
	uint8_t cycles;

	switch(msg) {
		case U8X8_MSG_DELAY_NANO:  // delay arg_int * 1 nano second
			// At 20Mhz, each cycle is 50ns, the call itself is slower.
			break;
		case U8X8_MSG_DELAY_100NANO:       // delay arg_int * 100 nano seconds
			CyDelayCycles(6);
			break;
		case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
			CyDelayUs(10);
			break;
		case U8X8_MSG_DELAY_MILLI:  // delay arg_int * 1 milli second
			CyDelay(1);
			break;
		default:
			return 0;
	}
	return 1;
}
