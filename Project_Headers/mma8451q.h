/*
 * mma8451q.h
 *
 *  Created on: Jan 28, 2015
 *      Author: Harrison
 */
#include "support_common.h"
#include "mma845x_device.h"

#ifndef MMA8451Q_H_
#define MMA8451Q_H_

//void mma8451q_init();
void MMA845x_Init(void);
void MMA845x_Standby(void);
void MMA845x_Active(void);
int16_t* MMA845x_Get();

#endif /* MMA8451Q_H_ */
