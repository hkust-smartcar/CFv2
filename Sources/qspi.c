#include "qspi.h"
#include "support_common.h"
#include "uart.h"
#include <cstdint>
#include <cstdio>
#include <stdlib.h>

void delay(void);
void chip_select(QSPI qspi);
void chip_deselect(QSPI qspi);
uint8_t qspi_byte(uint8_t data);

void delay(void){
	int i;
	for(i = 0; i < 5; i++){
		__asm__ __volatile__("nop");
	}
}

void qspi_init(QSPI qspi, QSPI_MODE mode, uint32_t baudrate){
	
	MCF_SCM_PPMRH &= ~MCF_SCM_PPMRH_CDGPIO;
	MCF_SCM_PPMRL &= ~MCF_SCM_PPMRL_CDQSPI;
	
//	MCF_GPIO_PQSPAR &= ~(PQSPAR_PQSPAR01_BITMASK | PQSPAR_PQSPAR11_BITMASK | PQSPAR_PQSPAR21_BITMASK |
//			PQSPAR_PQSPAR31_BITMASK | PQSPAR_PQSPAR41_BITMASK | PQSPAR_PQSPAR51_BITMASK | PQSPAR_PQSPAR61_BITMASK);
//	MCF_GPIO_PQSPAR |= PQSPAR_PQSPAR00_BITMASK | PQSPAR_PQSPAR10_BITMASK | PQSPAR_PQSPAR20_BITMASK;
	MCF_GPIO_PQSPAR &= ~(MCF_GPIO_PQSPAR_PQSPAR0(0) | MCF_GPIO_PQSPAR_PQSPAR1(0) | 
			MCF_GPIO_PQSPAR_PQSPAR2(0) | MCF_GPIO_PQSPAR_PQSPAR3(0) | 
			MCF_GPIO_PQSPAR_PQSPAR4(0) | MCF_GPIO_PQSPAR_PQSPAR5(0) | MCF_GPIO_PQSPAR_PQSPAR6(0));
	MCF_GPIO_PQSPAR |= MCF_GPIO_PQSPAR_QSPI_DOUT_DOUT | MCF_GPIO_PQSPAR_QSPI_DIN_DIN | MCF_GPIO_PQSPAR_QSPI_CLK_CLK;
	
	switch(qspi){
		case QSPI0:
			MCF_GPIO_PQSPAR |= MCF_GPIO_PQSPAR_QSPI_CS0_CS0;
			break;
			
		case QSPI2:
			MCF_GPIO_PQSPAR |= MCF_GPIO_PQSPAR_QSPI_CS2_CS2;
			break;
			
		case QSPI3:
			MCF_GPIO_PQSPAR |= MCF_GPIO_PQSPAR_QSPI_CS3_CS3;
			break;
	}
	
	if(baudrate > 1){
		uint8_t baud = (uint8_t)(80000000L / (baudrate * 2));
		MCF_QSPI_QMR |= baud;
	}
	
	MCF_QSPI_QMR &= ~(MCF_QSPI_QMR_CPOL | MCF_QSPI_QMR_CPHA);
	MCF_QSPI_QMR |= (mode << 8);
		
	MCF_QSPI_QAR = 0x20;
	MCF_QSPI_QDR |= MCF_QSPI_QDR_DATA(0x0f00);
	MCF_QSPI_QDR &= ~MCF_QSPI_QDR_DATA(0xf000);
	MCF_QSPI_QMR |= MCF_QSPI_QMR_MSTR | MCF_QSPI_QMR_BITS(8);
	MCF_QSPI_QDLYR |= MCF_QSPI_QDLYR_SPE | 0xff;
	MCF_QSPI_QWR |= MCF_QSPI_QWR_CSIV;
	MCF_QSPI_QIR |= MCF_QSPI_QIR_SPIF;
}


void chip_select(QSPI qspi){

	MCF_QSPI_QAR = 0x20;
	switch(qspi){
		case QSPI0:
			MCF_QSPI_QDR &= ~MCF_QSPI_QDR_QSPI_CS0;
			break;
			
		case QSPI2:
			MCF_QSPI_QDR &= ~MCF_QSPI_QDR_QSPI_CS2;
			break;
			
		case QSPI3:
			MCF_QSPI_QDR &= ~MCF_QSPI_QDR_QSPI_CS3;
			break;
	}

	//delay();
}

void chip_deselect(QSPI qspi){

	MCF_QSPI_QAR = 0x20;
	switch(qspi){
	case QSPI0:
		MCF_QSPI_QDR |= MCF_QSPI_QDR_QSPI_CS0;
		break;
		
	case QSPI2:
		MCF_QSPI_QDR |= MCF_QSPI_QDR_QSPI_CS2;
		break;
		
	case QSPI3:
		MCF_QSPI_QDR |= MCF_QSPI_QDR_QSPI_CS3;
		break;
	}
	delay();
}

uint8_t qspi_byte(uint8_t data)
{
	char ch[128];
	sprintf(ch, "s:%x\n", MCF_QSPI_QDLYR);
	uart_putstr(1,ch);
	sprintf(ch, "%x\n", MCF_QSPI_QIR);
	uart_putstr(1,ch);
	while (!(MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)){}
	MCF_QSPI_QAR = 0x00;
	MCF_QSPI_QDR = data;
	MCF_QSPI_QIR |= MCF_QSPI_QIR_SPIF;
	MCF_QSPI_QDLYR |= MCF_QSPI_QDLYR_SPE;
	while (!(MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)){}
	MCF_QSPI_QAR = 0x10;
	sprintf(ch, "e:%x\n", MCF_QSPI_QDLYR);
	uart_putstr(1,ch);
	sprintf(ch, "%x\n", MCF_QSPI_QIR);
	uart_putstr(1,ch);
	return (uint8_t)MCF_QSPI_QDR;
}

uint8_t qspi_write(QSPI qspi, uint8_t byte){
	chip_select(qspi);
	qspi_byte(byte);	
	chip_deselect(qspi);
}

uint8_t qspi_write_cmd(QSPI qspi, uint8_t reg, uint8_t cmd){
	uint8_t value = 0;
	chip_select(qspi);
	qspi_byte(reg);	
	value = qspi_byte(cmd);	
	chip_deselect(qspi);	
	return value;
}


uint8_t qspi_read_data(QSPI qspi, uint8_t reg){
	uint8_t value = 0;
	chip_select(qspi);
	qspi_byte(reg);
	value = qspi_byte(0x00);
	chip_deselect(qspi);
	return value;
}

void qspi_write_nbytes(QSPI qspi, uint8_t reg, uint8_t length, uint8_t * pdata){
	int i = 0;
	chip_select(qspi);
	qspi_byte(reg);
	for(i = 0; i < length; i++){
		qspi_byte(*(pdata + i));
	}
	chip_deselect(qspi);
}

void qspi_read_nbytes(QSPI qspi, uint8_t reg, uint8_t length, uint8_t * pdata){
	int i = 0;
	chip_select(qspi);
	qspi_byte(reg);
	for(i = 0; i < length; i++){
		*(pdata + i) = qspi_byte(0x00);
	}
	chip_deselect(qspi);
} 
  
