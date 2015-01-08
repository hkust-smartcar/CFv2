/*
 * mpu6050.c
 *
 *  Created on: Jan 3, 2015
 *      Author: Harrison
 */
#include <stdio.h>
#include "mpu6050.h"
#include "mpu6050_device.h"
#include "support_common.h"
#include "i2c_master.h"
#include "uart.h"

uint8 g_gyro_range = 2;
uint8 g_accel_range = 2;

float g_accel[3];
float g_temp;
float g_omega[3];

void mpu6050_init(){
	uint8 gyro_config;
	uint8 accel_config;
	
	I2CInit();

	I2CWriteByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, 0x00);
	
//	//Register 25 – Sample Rate Divider: Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
//	//Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG = 0 or 7)
	I2CWriteByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_SMPLRT_DIV, 0x00);

	//	//Register 26 - CONFIG: EXT_SYNC_SET[2:0]<<3 | DLPF_CFG[2:0];
//	//EXT_SYNC_SET=0, Input disabled;
//	//DLPF_CFG=0, Accel = 260Hz, Gyroscope = 256Hz;
	I2CWriteByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_CONFIG, 0x00);
//
//	//Register 27 - GYRO_CONFIG: FS_SEL[1:0] << 3;
//	//FS_SEL=0, ± 250 °/s; FS_SEL=1, ± 500 °/s; FS_SEL=2, ± 1000 °/s; FS_SEL=3, ± 2000 °/s;
	gyro_config = (g_gyro_range) << 3;
	I2CWriteByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, gyro_config);
//
//	//Register 28 - ACCEL_CONFIG: AFS_SEL[1:0] << 3;
//	//AFS_SEL=0, ±2g; AFS_SEL=1, ±4g; AFS_SEL=2, ±8g; AFS_SEL=3, ±16g;
	accel_config = (g_accel_range) << 3;
	I2CWriteByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, accel_config);
}

float GetAccelScaleFactor(){
	switch (g_accel_range)
	{
	default:
	case 0:
		return 16384.0f;

	case 1:
		return 8192.0f;

	case 2:
		return 4096.0f;

	case 3:
		return 2048.0f;
	}
}

float GetGyroScaleFactor(){
	switch (g_gyro_range)
	{
	default:
	case 0:
		return 131.0f;

	case 1:
		return 65.5f;

	case 2:
		return 32.8f;

	case 3:
		return 16.4f;
	}
}

void mpu6050_update(){
	uint8* data = I2CReadBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 14);
	uint16_t raw_accel[3];
	uint16_t raw_gyro[3];
	int i;
	
	for (i = 0; i < 14; i += 2)
	{
		if (i <= 5)
		{
			const int j = i / 2;
			raw_accel[j] = data[i] << 8 | data[i + 1];
			g_accel[j] = (float)raw_accel[j] / GetAccelScaleFactor();
		}
		else if (i == 6)
		{
			const uint16_t raw_temp = data[i] << 8 | data[i + 1];
			g_temp = (float)raw_temp / 340 + 36.53;
		}
		else
		{
			const int j = (i - 8) / 2;
			raw_gyro[j] = data[i] << 8 | data[i + 1];
			g_omega[j] = (float)raw_gyro[j] / GetGyroScaleFactor();
		}
	}
}

float GetTemp(){
	return g_temp;
}

float GetOmega(){
	return g_omega[0];
}

//float* GetOmega(){
//	return g_omega;
//}

