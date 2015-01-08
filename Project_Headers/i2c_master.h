/*
 * i2c_master.h
 *
 *  Created on: Jan 8, 2015
 *      Author: Harrison
 */
#include "support_common.h"

#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

void I2CInit();

void I2CWait();


void I2CAcquireBus();

void I2CReset();

void I2CStart();

void I2CRepeatedStart();

void I2CStop();

void I2CSend(uint8_t data, uint8_t ack);


uint8_t I2CGet(uint8_t ack);

void I2CWriteByte(uint8_t address, uint8_t reg, uint8_t data);

void I2CWriteBytes(uint8_t address, uint8_t reg, uint8_t* data, int size);

uint8_t I2CReadByte(uint8_t address, uint8_t reg);

uint8_t* I2CReadBytes(uint8_t address, uint8_t reg, int size);

#endif /* I2C_MASTER_H_ */
