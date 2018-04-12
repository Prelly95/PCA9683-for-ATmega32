#ifndef PCA9685_H
#define PCA9685_H

#define PCA9685_MODE1_SETTINGS	0x01
#define PCA9685_MODE2_SETTINGS	0x04

#define PCA9685_ADDRESS		0xA0		//SET THIS WITH DIP SWITCH [1 A5 A4 A3 A2 A1 A0 #R/W]
#define PCA9685_CLOCK_SPEED 25000000	//Device clock speed

#define PCA9685_MODE1		0x00		//mode 1 register address
#define PCA9685_MODE2		0x01		//mode 2 register address
#define PCA9685_CHANNEL0	0x06		//First Channel L Address
#define PCA9685_SUBADR1		0x02		//I2C Sub address 1
#define PCA9685_SUBADR2		0x03		//I2C Sub address 2
#define PCA9685_SUBADR3		0x04		//I2C Sub address 3
#define PCA9685_ALL_CALLADR	0x05		//All Call address
#define PCA9685_ALL_CHANNEL	0xFA		//All Channel L Address
#define PCA9685_PRE_SCALE	0xFE		//Pre Scale setting address
#define PCA9685_TEST_MODE	0xFF		//Test Mode Address

//MODE 1 Bits
#define RESTART				7			//RESTART bit
#define EXTCLOCK			6			//EXTCLOCK bit
#define AI					5			//Auto Incrament bit
#define SLEEP				4			//Sleep bit
#define SUB1				3			//SUB Address 1 bit
#define SUB2				2			//SUB Address 2 bit
#define SUB3				1			//SUB Address 3 bit
#define ALLCALL				0			//ALLCALL bit

//MODE 2 Bits
#define	INVRT				4			//Invert Output
#define	OCH					3			//0: Outputs change on STOP command - 1: Change on ACK
#define	OUTDRV				2			//output drive mode, 0: open-drain - 1: totem pole
/*OUTNE[1:0]
				00: when !OE = 1, CHANNELn = 0
				01: when !OE = 1 and OUTDRV = 1, CHANNELn = 1
				01: when !OE = 1 and OUTDRV = 0, CHANNELn = High Impedence
				1X:	when !OE = 1, CHANNELn = High Impedence
*/
#define	OUTNE1				1
#define OUTNE0				0


uint8_t PCA9685_Init(void);
uint8_t PCA9685_Restart(void);
uint8_t PCA9685_Sleep(void);
uint8_t PCA9685_SetPWMFreq(uint16_t freq);
uint8_t PCA9685_SetPinPWM(uint8_t channel, uint16_t ON, uint16_t OFF);
uint8_t PCA9685_WriteReg(uint8_t reg, uint8_t data);
uint8_t PCA9685_ReadReg(uint8_t reg, uint8_t *data);
void PCA9685_PrintSettings(void);

#endif
