/*
 * gpio.h
 *
 *  Created on: Dec 31, 2014
 *      Author: Harrison
 */
#include "support_common.h"
#ifndef GPIO_H_
#define GPIO_H_

typedef enum{
	PTTI = 0x4,
	PTTJ = 0x6,
	PTNQ = 0x8,
	PTAN = 0xA,
	PTAS = 0xB,
	PTQS = 0xC,
	PTTA = 0xE,
	PTTC = 0xF,
	PTUA = 0x11,
	PTUB = 0x12,
	PTUC = 0x13
}PTn;

typedef enum{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}PINn;

typedef enum{
	PRIMARY = 1,
	ALT1 = 2,
	ALT2 = 3,
	GPIO = 0
}FUNC;

typedef enum{
	IN = 0,
	OUT = 1
}DDR;

typedef enum{
	CLR = 0,
	SET = 1,
	UNKNOWN = 2
}STATE;

void gpio_init(PTn port, PINn pin, FUNC function, DDR dir, STATE state);
void gpio_set_func(PTn port, PINn pin, FUNC function);
void gpio_set_ddr(PTn port, PINn pin, DDR dir);
void gpio_set(PTn port, PINn pin, STATE state);
void gpio_clr(PTn port, PINn pin);
uint8_t gpio_get(PTn port, PINn pin);



#endif /* GPIO_H_ */
