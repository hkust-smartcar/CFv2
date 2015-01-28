/*
 * i2c_master.c
 *
 *  Created on: Jan 8, 2015
 *      Author: Harrison
 */
#include <stdlib.h>
#include "i2c_master.h"
#include "delay.h"
int is_inited = 0;
void I2CInit(){
	if(is_inited) return;
	
	uint8 temp;

	MCF_SCM_PPMRL &= ~MCF_SCM_PPMRL_CDI2C0;

	/* Enable the I2C signals */
	MCF_GPIO_PASPAR |= ( MCF_GPIO_PASPAR_SCL0_SCL0 | MCF_GPIO_PASPAR_SDA0_SDA0);

	/* set the frequency near 400KHz, see MCF52223RM table for details */ 
	MCF_I2C_I2FDR(0) = MCF_I2C_I2FDR_IC(0x32);

		
	MCF_I2C_I2CR(0) |= MCF_I2C_I2CR_IEN;
	
	/* start the module */
	I2CReset();

	/* if bit busy set, send a stop condition to slave module */
	if( MCF_I2C_I2SR(0) & MCF_I2C_I2SR_IBB)
	{
		//clear control register 
		MCF_I2C_I2CR(0) = 0;			

//		 enable module and send a START condition			
		MCF_I2C_I2CR(0) = MCF_I2C_I2CR_IEN | MCF_I2C_I2CR_MSTA;

//		 dummy read 			   		
		temp = MCF_I2C_I2DR(0);	

//		 clear status register 				
		MCF_I2C_I2SR(0) = 0;	

//		 clear control register 					
		MCF_I2C_I2CR(0) = 0;				

//		 enable the module again 		
		MCF_I2C_I2CR(0) = MCF_I2C_I2CR_IEN;	
	}
	
	is_inited = 1;
}

void I2CWait(){
	delay_us(1);
}

void I2CAcquireBus() {
	// Loop until I2C bus busy (IBB) becomes 0
	while(MCF_I2C0_I2SR & MCF_I2C_I2SR_IBB) {}
}

void I2CReset(){
	MCF_I2C_I2CR(0) |= MCF_I2C_I2CR_IIEN;
	MCF_I2C_I2CR(0) &= ~MCF_I2C_I2CR_MSTA;
	MCF_I2C_I2CR(0) &= ~MCF_I2C_I2CR_MTX;
	MCF_I2C_I2CR(0) &= ~MCF_I2C_I2CR_TXAK;
}

void I2CStart(){
	I2CAcquireBus();
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_MTX; // Make board a transmitter
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_MSTA; // Make board a master (which sends the start bit)
}

void I2CRepeatedStart(){
	MCF_I2C0_I2CR |= MCF_I2C_I2CR_RSTA;
}

void I2CStop(){
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_MSTA); // Make board a slave and send Stop bit
	I2CReset();
}

void I2CSend(uint8_t data){

	MCF_I2C_I2DR(0) = data;
	//Check interrupt flag if transfer is done
	while(!(MCF_I2C0_I2SR & MCF_I2C_I2SR_IIF)) {}
//	while(MCF_I2C0_I2SR & MCF_I2C_I2SR_RXAK) {}
	//Clear interrupt flag
	MCF_I2C0_I2SR &= ~(MCF_I2C_I2SR_IIF);
	

	I2CWait();
}

uint8_t I2CGet(){
	uint8_t data;

	data = MCF_I2C_I2DR(0);
	//Check interrupt flag if transfer is done
	while(!(MCF_I2C0_I2SR & MCF_I2C_I2SR_IIF)) {}
//	while(MCF_I2C0_I2SR & MCF_I2C_I2SR_RXAK) {}
	//Clear interrupt flag
	MCF_I2C0_I2SR &= ~(MCF_I2C_I2SR_IIF);
	
	I2CWait();
	return data;
}

void I2CWriteByte(uint8_t address, uint8_t reg, uint8_t data){
	I2CStart();
//	//Enable Ack
//	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	I2CSend((address << 1));
	I2CSend(reg);
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	I2CSend(data);
	I2CStop();
}

void I2CWriteBytes(uint8_t address, uint8_t reg, uint8_t* data, int size){
	I2CStart();
	//Enable Ack
//	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	I2CSend(address << 1 | 0x0);
	I2CSend(reg);
	for(int i = 0; i<size-1; i++){
		I2CSend(data[i]);
	}
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	I2CSend(data[size-1]);
	I2CStop();
}

uint8_t I2CReadByte(uint8_t address, uint8_t reg){
	uint8_t data;
	I2CStart();
	
//	Transmit the calling address via the I2DRn.
	I2CSend((address << 1));
//	Check I2SRn[IBB]. If it is clear, wait until it is set and go to step #1.
	while(!(MCF_I2C0_I2SR & MCF_I2C_I2SR_IBB)) {}
		
	I2CSend(reg);
	
	I2CRepeatedStart();
	I2CSend((address << 1) | 0x1);
	
	//Become a receiver
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_MTX);
	//Enable Ack
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	uint8_t dummy = I2CGet();
	
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	data = I2CGet();
	
	I2CStop();
	return data;
}

uint8_t* I2CReadBytes(uint8_t address, uint8_t reg, int size){
	uint8_t data[size];
	
	I2CStart();
	
//	Transmit the calling address via the I2DRn.
	I2CSend((address << 1));
//	Check I2SRn[IBB]. If it is clear, wait until it is set and go to step #1.
	while(!(MCF_I2C0_I2SR & MCF_I2C_I2SR_IBB)) {}
		
	I2CSend(reg);
	
	I2CRepeatedStart();
	I2CSend((address << 1) | 0x1);
	
	//Become a receiver
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_MTX);
	//Enable Ack
	MCF_I2C0_I2CR &= ~(MCF_I2C_I2CR_TXAK);
	uint8_t dummy = I2CGet();
	
	for(int i=0; i<size-1; i++){
		data[i] = I2CGet();
	}
	
	//Disable Ack
	MCF_I2C0_I2CR |= (MCF_I2C_I2CR_TXAK);
	data[size-1] = I2CGet();
	
	I2CStop();
	
	return data;
}
