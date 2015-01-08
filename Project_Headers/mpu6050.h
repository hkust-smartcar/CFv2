/*
 * mpu6050.h
 *
 *  Created on: Jan 5, 2015
 *      Author: Harrison
 */

#ifndef MPU6050_H_
#define MPU6050_H_



void mpu6050_init();
float GetAccelScaleFactor();
float GetGyroScaleFactor();
void mpu6050_update();
float GetTemp();
float GetOmega();
//float* GetOmega(){
//	return g_omega;
//}

#endif /* MPU6050_H_ */
