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
uint16_t GetTemp();
uint16_t* GetOmega();
uint16_t* GetAccel();

#endif /* MPU6050_H_ */
