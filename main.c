#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/twi.h>
#include <util/atomic.h>
#include "uart.h"
#include "cmd_line_buffer.h"
#include "cmd_parser.h"
#include "i2c.h"
#include "pca9685.h"


CLB_CREATE_STATIC(clb, 80);


int main(void)
{
    uart_init();
	I2C_Init();
	PCA9685_Init();

    // Enable global interrupts
    sei();

	_delay_ms(500);
	// Send initial string
	printf_P(PSTR("\014")); //clear terminal
	printf_P(PSTR("\nHello world! %x\n\n"), 17);

	//prints out the modes and settings registers
	PCA9685_PrintSettings();

	_delay_ms(500);

	//set some test/example outputs
	PCA9685_SetPinPWM(0, 0x0E65, 0x0CCB);
	PCA9685_SetPinPWM(1, 0x0199, 0x04CC);
	PCA9685_SetPinPWM(2, 0x0199, 0x04CC);

	_delay_ms(1000);

	//Test the sleep functionality
	PCA9685_Sleep();

	_delay_ms(1000);

	//restart using i2c library to test the functionality is the same
	I2C_WriteBit(PCA9685_ADDRESS, PCA9685_MODE1, RESTART, 1);

    for(;/*ever*/;)
    {
		//cycles through some test pwm signams on channel 0
		PCA9685_SetPinPWM(0, 0x0E65, 0x0CCB);
		_delay_ms(1000);
		PCA9685_SetPinPWM(0, 0x0199, 0x04CC);
		_delay_ms(1000);
		PCA9685_SetPinPWM(0, 0x0E65, 0x0CCB);
		_delay_ms(1000);
		PCA9685_SetPinPWM(0, 0x0199, 0x04CC);
		_delay_ms(1000);
		PCA9685_SetPinPWM(0, 0x0E65, 0x0CCB);
		_delay_ms(1000);
		PCA9685_SetPinPWM(0, 0x0199, 0x04CC);
		_delay_ms(1000);

		//comand process unrelated to pca
        clb_process(&clb);
    }
    return 0;
}
