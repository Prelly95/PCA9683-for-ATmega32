#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "i2c.h"
#include "pca9685.h"


uint8_t PCA9685_Init(void)
{
	PCA9685_WriteReg(PCA9685_MODE1, 0x11);//Reset device
	PCA9685_SetPWMFreq(1000);
	PCA9685_WriteReg(PCA9685_MODE1, PCA9685_MODE1_SETTINGS);//Reset device
	PCA9685_WriteReg(PCA9685_MODE2, PCA9685_MODE2_SETTINGS);//Reset device
	return 0;
}

uint8_t PCA9685_WriteReg(uint8_t reg, uint8_t data)
{
	if(I2C_WriteReg(PCA9685_ADDRESS, reg, 1, &data))
	{
		printf_P(PSTR("ERROR 1\n"));
		return 1;
	}
	return 0;
}

uint8_t PCA9685_ReadReg(uint8_t reg, uint8_t *data)
{
	if(I2C_ReadReg(PCA9685_ADDRESS, reg, 1, data))
	{
		printf_P(PSTR("ERROR 1\n"));
		return 1;
	}
	return 0;
}

uint8_t PCA9685_Sleep(void)
{
	if(I2C_WriteBit(PCA9685_ADDRESS, PCA9685_MODE1, SLEEP, 1))
	{
		return 1;
	}
	return 0;
}

uint8_t PCA9685_SetPWMFreq(uint16_t freq)
{
	uint8_t prescale;

	freq = (freq > 1000 ? 1000 : (freq < 40 ? 40 : freq));
	prescale = (uint8_t)((PCA9685_CLOCK_SPEED / 4096 / freq)  - 1);

	PCA9685_Sleep();
	PCA9685_WriteReg(PCA9685_PRE_SCALE, prescale);
	I2C_WriteBit(PCA9685_ADDRESS, PCA9685_MODE1, RESTART, 1);

	// PCA9685_WriteReg(PCA9685_MODE1, 0x11);//Reset device
	// PCA9685_WriteReg(PCA9685_PRE_SCALE, prescale);
	// PCA9685_WriteReg(PCA9685_MODE1, 0x01);//Reset device
	_delay_ms(1);

	return 0;
}

uint8_t PCA9685_SetPinPWM(uint8_t channel, uint16_t ON, uint16_t OFF)
{
	uint8_t ON_H;
	uint8_t ON_L;
	uint8_t OFF_H;
	uint8_t OFF_L;
	uint8_t channelReg;

	ON_H = (uint8_t)(ON >> 8);						//high bits of ON
	ON_L = (uint8_t)(ON & 0x00FF);					//high bits of ON

	OFF_H = (uint8_t)(OFF >> 8);					//high bits of ON
	OFF_L = (uint8_t)(OFF & 0x00FF);				//high bits of ON

	channelReg = PCA9685_CHANNEL0 + 4*(channel);	//calculates the register of the channel to set

	PCA9685_WriteReg(channelReg, ON_L);				//write LED_ON low
	PCA9685_WriteReg(channelReg+1, ON_H);				//write LED_ON high
	PCA9685_WriteReg(channelReg+2, OFF_L);				//write LED_OFF low
	PCA9685_WriteReg(channelReg+3, OFF_H);				//write LED_OFF high

	return 0;
}


void PCA9685_PrintSettings(void)
{
	uint8_t regCheck = 0;
	PCA9685_ReadReg(PCA9685_MODE1, &regCheck);
	printf_P(PSTR("\n\nMode 1 value: %i\n"), regCheck);

	PCA9685_ReadReg(PCA9685_MODE2, &regCheck);
	printf_P(PSTR("Mode 2 value: %i\n"), regCheck);

	PCA9685_ReadReg(PCA9685_SUBADR1, &regCheck);
	printf_P(PSTR("Sub Address 1: %i\n"), regCheck);

	PCA9685_ReadReg(PCA9685_SUBADR2, &regCheck);
	printf_P(PSTR("Sub Address 2: %i\n"), regCheck);

	PCA9685_ReadReg(PCA9685_SUBADR3, &regCheck);
	printf_P(PSTR("Sub Address 3: %i\n"), regCheck);

	PCA9685_ReadReg(PCA9685_ALL_CALLADR, &regCheck);
	printf_P(PSTR("All Call Value: %i\n"), regCheck);

	PCA9685_ReadReg(PCA9685_PRE_SCALE, &regCheck);
	printf_P(PSTR("Prescale Value: %i\n"), regCheck);

	PCA9685_ReadReg(PCA9685_TEST_MODE, &regCheck);
	printf_P(PSTR("Test Mode: %i\n\n"), regCheck);
}
