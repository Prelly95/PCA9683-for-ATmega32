#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/twi.h>
#include "uart.h"
#include "cmd_line_buffer.h"
#include "cmd_parser.h"
#include "i2c.h"
#include "pca9685.h"

CLB_CREATE_STATIC(clb, 80);

int16_t x = 0;
int16_t y = 0;
int16_t z = 0;

uint8_t b;

int main(void)
{
    uart_init();
	I2C_Init();
	PCA9685_Init();

    // Enable global interrupts
    sei();

	_delay_ms(1000);

	// Send initial string
	printf_P(PSTR("\nHello world!\n\n"));

	_delay_ms(1000);

	PCA9685_ReadReg(PCA9685_MODE1, &b);
	printf_P(PSTR("%i\n"), b);

    for(;/*ever*/;)
    {
        clb_process(&clb);
    }
    return 0;
}
