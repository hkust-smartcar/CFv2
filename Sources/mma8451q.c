/*
 * mma8451q.c
 *
 *  Created on: Jan 28, 2015
 *      Author: Harrison
 */
#include "mma8451q.h"
#include "mma845x_device.h"
#include "i2c_master.h"
#include "lcd.h"

//void mma8451q_init(){
//	I2CInit();
//	uint8_t whoami = I2CReadByte(0x1A, 0x0D);
//	char s[100];
//	sprintf(s, "whoami: %x \n", whoami);
//	LcdDrawString(0, 2*FONT_H, s, ~0, 0);
//	
//	
//}

/***********************************************************************************************\
 * Freescale MMA8451,2,3Q Driver
 *
 * Filename: mma845x.c
 *
 *
 * (c) Copyright 2010, Freescale, Inc.  All rights reserved.
 *
 * No part of this document must be reproduced in any form - including copied,
 * transcribed, printed or by any electronic means - without specific written
 * permission from Freescale Semiconductor.
 *
\***********************************************************************************************/

/***********************************************************************************************\
 * Private macros
\***********************************************************************************************/

/***********************************************************************************************\
 * Private type definitions
\***********************************************************************************************/

/***********************************************************************************************\
 * Private prototypes
\***********************************************************************************************/

/***********************************************************************************************\
 * Private memory declarations
\***********************************************************************************************/

/***********************************************************************************************\
 * Public memory declarations
\***********************************************************************************************/

#pragma DATA_SEG __SHORT_SEG _DATA_ZEROPAGE

uint8_t SlaveAddressIIC;

//#pragma DATA_SEG DEFAULT

/***********************************************************************************************\
 * Public functions
\***********************************************************************************************/
int16_t* MMA845x_Get(){
	uint8_t status = I2CReadByte(SlaveAddressIIC, STATUS_00_REG);
	uint8_t* value;
	int16_t accel[3];
	/*ZYXDR_BIT == 1*/
	if ((status>>3 & 1) == 1)
	{
		/*
		 **  Read the  XYZ sample data
		 */
			value = I2CReadBytes(SlaveAddressIIC, OUT_X_MSB_REG, 6);
		/*
		 **  Output results
		 */
			accel[0] = (int16_t)((value[0]<<8) | value[1])/4*10000/4096;
			accel[1] = (int16_t)((value[2]<<8) | value[3])/4*10000/4096;
			accel[2] = (int16_t)((value[4]<<8)|value[5])/4*10000/4096;
			
	}
	return accel;
}



/*********************************************************\
 * Put MMA845xQ into Active Mode
\*********************************************************/
void MMA845x_Active ()
{
	I2CWriteByte(SlaveAddressIIC, CTRL_REG1, (I2CReadByte(SlaveAddressIIC, CTRL_REG1) | ACTIVE_MASK));
}

/*********************************************************\
 * Put MMA845xQ into Standby Mode
\*********************************************************/
void MMA845x_Standby (void)
{
	uint8_t n;
	/*
	 **  Read current value of System Control 1 Register.
	 **  Put sensor into Standby Mode.
	 **  Return with previous value of System Control 1 Register.
	 */
	n = I2CReadByte(SlaveAddressIIC, CTRL_REG1);
	I2CWriteByte(SlaveAddressIIC, CTRL_REG1, n & ~ACTIVE_MASK);
}

/*********************************************************\
 * Initialize MMA845xQ
\*********************************************************/
void MMA845x_Init (void)
{
	SlaveAddressIIC = MMA845x_IIC_ADDRESS;
	I2CInit();
	MMA845x_Standby();
	/*
	 **  Configure sensor for:
	 **    - Sleep Mode Poll Rate of 50Hz (20ms)
	 **    - System Output Data Rate of 200Hz (5ms)
	 **    - Full Scale of +/-2g
	 */
	I2CWriteByte(SlaveAddressIIC, CTRL_REG1, ASLP_RATE_20MS+DATA_RATE_5MS);
	I2CWriteByte(SlaveAddressIIC, XYZ_DATA_CFG_REG, FULL_SCALE_2G);
}

/***********************************************************************************************\
 * Private functions
\***********************************************************************************************/
int16_t MMA845x_GetAngle(){
	
}
