/*
 * tsl1401.h
 *
 *  Created on: Jan 28, 2015
 *      Author: Harrison
 */
#include "support_common.h"

#ifndef TSL1401_H_
#define TSL1401_H_

void tsl1401_init();
void tsl1401_collect(void);
uint32* GetCCD();
uint32 GetCCDAvg();

#endif /* TSL1401_H_ */
