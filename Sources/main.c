/*
 * main implementation: use this sample to create your own application
 *
 */
#include <cstdint>
#include <cstdio>
#include <stdlib.h>

#include "support_common.h" /* include peripheral declarations and more */
#include "delay.h"
#include "uart.h"
#include "qspi.h"
#include "lcd.h"
#include "pit.h"
#include "gpio.h"
#include "mpu6050.h"
#include "mpu6050_device.h"
#include "exceptions.h"
#include "interrupts.h"
#include "i2c_master.h"
#include "adc.h"
#include "pwm.h"
#include "gpt.h"
#include "dtim.h"


volatile uint32_t g_counter = 0;
__interrupt__  void pit_isr_handler(){
	g_counter++;
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
}

char* s;
extern uint16_t* g_omega;

int main(void)
{
	int on = 1;
	g_counter = 0;
	
	/*GPIO tests*/
	gpio_init(PTTJ, PIN4, GPIO, OUT, CLR);
	gpio_init(PTTJ, PIN1, GPIO, OUT, SET);
	gpio_init(PTTJ, PIN2, GPIO, OUT, SET);
	gpio_init(PTTJ, PIN6, GPIO, OUT, CLR);
	gpio_init(PTTJ, PIN7, GPIO, OUT, CLR);
	
	gpio_init(PTTJ, PIN3, GPIO, IN, UNKNOWN);
	gpio_init(PTTJ, PIN4, GPIO, IN, UNKNOWN);
	gpio_init(PTTJ, PIN5, GPIO, IN, UNKNOWN);
	gpio_init(PTTI, PIN0, GPIO, IN, UNKNOWN);
	gpio_init(PTTI, PIN1, GPIO, IN, UNKNOWN);
	
	gpio_init(PTTI, PIN3, GPIO, IN, UNKNOWN);
	gpio_init(PTTI, PIN5, GPIO, IN, UNKNOWN);
	gpio_init(PTTI, PIN6, GPIO, IN, UNKNOWN);
	
	gpio_init(PTTA, PIN0, GPIO, OUT, SET);
	
	/*DTIM_Info config = {
			0,	//active low or toggle output
			0,	//input clk divider
			1,	//rising, falling or both edge capture
			3,		//sysclk, sysclk/16 or DTINn input
			1,	//freerun or restart
			0,		//timer stop while core halted
			0,		//increment timer by 1 or by 65537
			0,		//DMA request enable
			0,
			0
	};*/
	dtim_init(0);
	dtim_start(0);
	
	/*GPIO tests*/
	
	gpio_init(PTTC, PIN3, GPIO, OUT, CLR);
	ADC_init(PIN5);
	
	
	/*uart tests*/
	uart_init(0,SYSTEM_CLOCK_KHZ,115200);
	
	/*uart tests*/
	LcdInit();
	LcdClear(0x0);

		
	PITInit(0);
	PIT_EnableInts(&pit_isr_handler, 0);
	PIT_Start(0);
	
	PWMInfo pwminfo = {
			1, //channel input clock
			0, //prescaler a
			1, //prescaler b
			0, //divisor of clock a to clock sa
			2, //divisor of clock b to clock sb
			0, //left align or center align mode
			0, //concatenate as 16bit
			0, //polarity
			0, //stop in doze mode
			0, //stop in debug mode
			10, //pwm output period
			3 //duty cycle
			
	};
	
	gpio_init(PTTC,PIN1, ALT2, OUT, UNKNOWN);
	PWMInit(pwminfo, 2);
	PWMEnable(2);
	
	gpio_init(PTTC,PIN1, GPIO, OUT, SET);
	
//	mpu6050_init();
	

	char s[100];
	int16_t* omega;
	uint16_t v=0;
	uint8_t up = 0, down = 0, right = 0, left = 0, center = 0;
	uint32_t count = 0;
	int on2 = 0;
	while(1){
		
		if(g_counter%1000==0){
			up = gpio_get(PTTJ, PIN3);
//			up = gpio_get(PTTI, PIN3);
			down = gpio_get(PTTJ, PIN4);
//			down = gpio_get(PTTI, PIN5);
			left = gpio_get(PTTJ, PIN5);
//			left = gpio_get(PTTI, PIN6);
			right = gpio_get(PTTI, PIN0);
			center = gpio_get(PTTI, PIN1);
//			mpu6050_update();
			v = ADonce(PIN5);
//			omega = GetOmega();
//			sprintf(s, "%d %d %d %d\0", omega[0], omega[1], omega[2], GetTemp());
			sprintf(s, "%d %d %d %d %d\0", up, down, left, right, center);
			LcdDrawString(0, 1, s, 0xFFF0,0x0000);
			count = DTimGetCount(0);
			sprintf(s, "%d                                       \0", count);
			LcdDrawString(0, 1*FONT_H, s, 0xFFF0,0x0000);
//			uart_putstr(0, s);
			if(on==1){
//				gpio_clr(PTTJ,PIN4);
				gpio_set(PTTJ, PIN1, SET);
				gpio_set(PTTJ, PIN2, SET);
				gpio_clr(PTTJ, PIN6);
				gpio_clr(PTTJ, PIN7);
				on=0;
			}else{
//				gpio_set(PTTJ,PIN4,SET);
				gpio_clr(PTTJ, PIN1);
				gpio_clr(PTTJ, PIN2);
				gpio_set(PTTJ, PIN6, SET);
				gpio_set(PTTJ, PIN7, SET);
				on=1;
			}
		}
	}


}
