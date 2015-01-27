#ifndef __ADC_H
#define __ADC_H

#include "MCF52255.h"
#include "gpio.h"

#define ADRSLT(x)                    (*(volatile uint16*)(&__IPSBAR[0x00190012UL] + ((x)*0x2)))
typedef enum{
	AN0 = 0,
	AN1,
	AN2,
	AN3,
	AN4,
	AN5,
	AN6,
	AN7
}ANn;

void ADC_init(PINn pin);
uint16 ADonce(PINn pin);

#endif
