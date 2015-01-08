/*
 * i2c_master.c
 *
 *  Created on: Jan 8, 2015
 *      Author: Harrison
 */
#include <stdlib.h>
#include "i2c_master.h"
#include "delay.h"

void I2CInit(){
	uint8 temp;

	MCF_SCM_PPMRL &= ~MCF_SCM_PPMRL_CDI2C0;

	/* Enable the I2C signals */
	MCF_GPIO_PASPAR |= ( MCF_GPIO_PASPAR_SCL0_SCL0 | MCF_GPIO_PASPAR_SDA0_SDA0);

	/* set the frequency near 400KHz, see MCF52223RM table for details */ 
	MCF_I2C_I2FDR(0) = MCF_I2C_I2FDR_IC(0x32);

	/* start the module */
	I2CReset();

	/* if bit busy set, send a stop condition to slave module */
	if( MCF_I2C_I2SR(0) & MCF_I2C_I2SR_IBB)
	{
		MCF_I2C0_I2CR = 0x00; // Board is slave-receiver, i2c disabled, interrupts disabled
		MCF_I2C0_I2CR = 0xA0; // Board is master-receiver, i2c enabled, interrupts, disabled
		uint8_t dummy = MCF_I2C0_I2DR; // Dummy read from slave which is transmitting
		MCF_I2C0_I2SR = 0x00; // Clear arbitration lost flag, clear i2c interrupt request flag
		MCF_I2C0_I2CR = 0x00; // Board is slave-receiver, i2c disabled, interrupts disabled
		MCF_I2C0_I2CR = 0x80; // Enable I2C module
		/* clear control register 
		MCF_I2C_I2CR(0) = 0;			

		 enable module and send a START condition			
		MCF_I2C_I2CR(0) = MCF_I2C_I2CR_IEN | MCF_I2C_I2CR_MSTA;

		 dummy read 			   		
		temp = MCF_I2C_I2DR(0);	

		 clear status register 				
		MCF_I2C_I2SR(0) = 0;	

		 clear control register 					
		MCF_I2C_I2CR(0) = 0;				

		 enable the module again 		
		MCF_I2C_I2CR(0) = MCF_I2C_I2CR_IEN;	*/
	}
}

void I2CWait(){
//	delay_us(0);
}

void I2CAcquireBus() {
	// Loop until I2C bus busy (IBB) becomes 0
	while(MCF_I2C0_I2SR & MCF_I2C_I2SR_IBB) {}
}

void I2CReset(){
//	MCF_I2C_I2CR(0) |= MCF_I2C_I2CR_IEN;
	MCF_I2C_I2CR(0) |= MCF_I2C_I2CR_IIEN;
	MCF_I2C_I2CR(0) &= ~MCF_I2C_I2CR_MSTA;
//	MCF_I2C_I2CR(0) &= ~MCF_I2C_I2CR_MTX;
//	MCF_I2C_I2CR(0) &= ~MCF_I2C_I2CR_TXAK;
}

void I2CStart(){
	I2CAcquireBus();
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_MTX; // Make board a transmitter
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_MSTA; // Make board a master (which sends the start bit)
}

void I2CRepeatedStart(){
	I2CAcquireBus();
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_RSTA;
}

void I2CStop(){
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_MSTA); // Make board a slave and send Stop bit
	I2CReset();
}

void I2CSend(uint8_t data, uint8_t ack){
//	if(ack){
//		//Enable Ack
//		MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
//	}else{
		//Disable Ack
//		MCF_I2C0_I2CR |= MCF_I2C_I2CR_TXAK;
//	}

	MCF_I2C_I2DR(0) = data;
	//Check interrupt flag if transfer is done
	while(!(MCF_I2C0_I2SR & MCF_I2C_I2SR_ICF)) {}
	//Clear interrupt flag
	MCF_I2C0_I2SR &= ~(MCF_I2C_I2SR_IIF);

	I2CWait();
}

uint8_t I2CGet(uint8_t ack){
	uint8_t data;
//	if(ack){
//		//Enable Ack
//		MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
//	}else{
//		//Disable Ack
//		MCF_I2C0_I2CR |= MCF_I2C_I2CR_TXAK;
//	}
	data = MCF_I2C_I2DR(0);
	//Check interrupt flag if transfer is done
//	while(!(MCF_I2C0_I2SR & MCF_I2C_I2SR_IIF)) {}
	while(!(MCF_I2C0_I2SR & MCF_I2C_I2SR_ICF)) {}
	//Clear interrupt flag
	MCF_I2C0_I2SR &= ~(MCF_I2C_I2SR_IIF);
	I2CWait();
	return data;
}

void I2CWriteByte(uint8_t address, uint8_t reg, uint8_t data){
	I2CStart();
	//Enable Ack
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	I2CSend(address << 1 | 0x0,1);
	I2CSend(reg,1);
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	I2CSend(data,0);
	I2CStop();
}

void I2CWriteBytes(uint8_t address, uint8_t reg, uint8_t* data, int size){
	I2CStart();
	//Enable Ack
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	I2CSend(address << 1 | 0x0,1);
	I2CSend(reg,1);
	for(int i = 0; i<size-1; i++){
		I2CSend(data[i],1);
	}
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	I2CSend(data[size-1],0);
	I2CStop();
}

uint8_t I2CReadByte(uint8_t address, uint8_t reg){
	uint8_t data;
	I2CStart();
	//Enable Ack
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	I2CSend(address << 1 | 0x0,1);
	I2CSend(reg,1);
	I2CRepeatedStart();
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_MTX); // Become a receiver
	I2CSend(address << 1 | 0x1,1);
	uint8_t dummy = I2CGet(1);
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	data = I2CGet(0);
	I2CStop();
	return data;
}

uint8_t* I2CReadBytes(uint8_t address, uint8_t reg, int size){
	uint8_t* data = (uint8_t*) malloc(size);
	I2CStart();
	//Enable Ack
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	I2CSend(address << 1 | 0x0,1);
	I2CSend(reg,1);
	I2CRepeatedStart();
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_MTX); // Become a receiver
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK); // Configure to ACK each recv'd data byte
	I2CSend(address << 1 | 0x1,1);
	uint8_t dummy = I2CGet(1);
	for(int i=0; i<size-1; i++){
		data[i] = I2CGet(1);
	}
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	data[size-1] = I2CGet(0);
	I2CStop();
	return data;
}
