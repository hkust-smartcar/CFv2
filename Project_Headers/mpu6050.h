/*
 * mpu6050.h
 *
 *  Created on: Jan 5, 2015
 *      Author: Harrison
 */
#ifndef MPU6050_H_
#define MPU6050_H_

#include "support_common.h"

void mpu6050_init();
float GetAccelScaleFactor();
float GetGyroScaleFactor();
void mpu6050_update();
int16_t GetTemp();
int16_t* GetOmega();
int16_t* GetAccel();

#endif /* MPU6050_H_ */
