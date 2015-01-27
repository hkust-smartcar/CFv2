/*
 * gpio.c
 *
 *  Created on: Dec 31, 2014
 *      Author: Harrison
 */

#include "gpio.h"

#define GPIO_PORT_OUTPUT_BASE (IPSBAR_ADDRESS + 0x100000)
const uint32 GPIO_PORT_DDR_BASE = (GPIO_PORT_OUTPUT_BASE + 0x18);
const uint32 GPIO_PORT_PIN_DATA_SET_BASE = (GPIO_PORT_OUTPUT_BASE + 0x30);
const uint32 GPIO_PORT_CLEAR_BASE = (GPIO_PORT_OUTPUT_BASE + 0x48);
const uint32 GPIO_PORT_PIN_ASSIGN_BASE = (GPIO_PORT_OUTPUT_BASE + 0x60);

#define GPIO_PAR(x) (*(vuint8 *)(GPIO_PORT_PIN_ASSIGN_BASE + x))
#define GPIO_DDR(x) (*(vuint8 *)(GPIO_PORT_DDR_BASE + x))
#define GPIO_PORT(x) (*(vuint8 *)(GPIO_PORT_OUTPUT_BASE + x))
#define GPIO_SET(x) (*(vuint8 *)(0x40100030 + x))

void gpio_init(PTn port, PINn pin, FUNC function, DDR dir, STATE state){
	gpio_set_func(port, pin, function);
	gpio_set_ddr(port, pin, dir);
	if(state==SET) {
		gpio_set(port, pin, state);
	}else if(state==CLR){
		gpio_clr(port, pin);
	}
}
void gpio_set_func(PTn port, PINn pin, FUNC function){
		switch(port){
		//Dual-function pins
		case PTTI:
		case PTTJ:
		case PTAN:
			GPIO_PAR(port) |= ((0x1 & function) << pin);
			break;
		//Quad-function pins
		case PTAS:
			GPIO_PAR(port) |= (((0x3 & function) << pin*2) & 0x3F);
			break;
		case PTQS:
			GPIO_PAR(port) |= (((0x3 & function) << pin*2) & 0x3CFF);
			break;
		case PTTA:
		case PTTC:
		case PTUA:
		case PTUB:
		case PTUC:
			GPIO_PAR(port) |= (((0x3 & function) << pin*2) & 0xFF);
			break;
		default:
			break;
		}
	
}
void gpio_set_ddr(PTn port, PINn pin, DDR dir){
	if(dir == OUT){
		GPIO_DDR(port) |= 1 << pin;
	}else{
		GPIO_DDR(port) &= ~(1 << pin);
	}
}
void gpio_set(PTn port, PINn pin, STATE state){
	if(state == SET){
		GPIO_PORT(port) |= 1 << pin;
	}else{
		GPIO_PORT(port) &= ~(1 << pin);
	}

}
void gpio_clr(PTn port, PINn pin){
	gpio_set(port, pin, CLR);
}

uint8_t gpio_get(PTn port, PINn pin){
	return (uint8_t) ((GPIO_SET(port) >> pin) & 0x1);
}

/*Add Pin Drive Strength*/
/*Add Pin Slew Rate*/
