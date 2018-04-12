#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/twi.h>
#include <avr/pgmspace.h>

#include "i2c.h"
#include "pca9685.h"


uint8_t PCA9685_Init(void)
{
	PCA9685_WriteReg(PCA9685_MODE1, 0x01);//setup mode 1
	PCA9685_WriteReg(PCA9685_MODE2, 0x00);//setup mode 2
	PCA9685_SetPWMFreq(1000);//set frequency
	return 0;
}

uint8_t PCA9685_WriteReg(uint8_t reg, uint8_t data)
{
	if(I2C_WriteReg(PCA9685_ADDRESS, reg, 1, &data))
	{
		return 1;
	}
	return 0;
}

uint8_t PCA9685_Restart(void)
{
	uint8_t data;

	PCA9685_ReadReg(PCA9685_MODE1, &data);
	if(data != (1<<SLEEP))
	{
		return 1;
	}

	data |= (1<<RESTART);

	PCA9685_WriteReg(PCA9685_MODE1, data);

	return 0;
}

uint8_t PCA9685_ReadReg(uint8_t reg, uint8_t *data)
{
	I2C_ReadReg(PCA9685_ADDRESS, reg, 1, data);

	return 0;
}

uint8_t PCA9685_Sleep(void)
{
	uint8_t data;

	PCA9685_ReadReg(PCA9685_MODE1, &data);

	data |= (1<<SLEEP);
	if(PCA9685_WriteReg(PCA9685_MODE1, data))
	{
		return 1;
	}

	return 0;
}

uint8_t PCA9685_SetPWMFreq(uint16_t freq)
{
	uint8_t prescale;

	freq = (freq > 1000 ? 1000 : (freq < 40 ? 40 : freq));
	prescale = (uint8_t)((PCA9685_CLOCK_SPEED/(4096*freq))-1);

	PCA9685_Sleep();
	PCA9685_WriteReg(PCA9685_PRE_SCALE, prescale);
	PCA9685_Restart();

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

	channelReg = PCA9685_CHANNEL0 + 4*(channel-1);	//calculates the register of the channel to set

	PCA9685_WriteReg(channelReg, ON_L);				//write LED_ON low
	PCA9685_WriteReg(channelReg, ON_H);				//write LED_ON high
	PCA9685_WriteReg(channelReg, OFF_L);			//write LED_OFF low
	PCA9685_WriteReg(channelReg, OFF_H);			//write LED_OFF high
	return 0;
}
