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
	/*GPIO tests*/
	
	gpio_init(PTTC, PIN3, GPIO, OUT, CLR);
	ADC_init(PIN5);
	
	/*uart tests*/
	uart_init(0,SYSTEM_CLOCK_KHZ,115200);
	
	/*uart tests*/
//	LcdInit();
//	LcdClear(0x0000);
//	LcdDrawString(0, 32, "CCD2\0", 0xFFF0,0x0000);

//	qspi_init(QSPI0, Q_MODE0, 1000000L);
		
	PITInit(0);
	PIT_EnableInts(&pit_isr_handler, 0);
	PIT_Start(0);

	mpu6050_init();

	char s[100];
	int16_t* omega;
	uint16_t v=0;
	while(1){
		mpu6050_update();
//		sprintf(s, "%d \n", (int16_t) GetTemp());

//		delay_ms(100);
		if(g_counter%1000==0){
			v = ADonce(PIN5);
			omega = GetOmega();
			sprintf(s, "%d %d %d %d %d %d\n", g_counter, v, omega[0], omega[1], omega[2], GetTemp());
			uart_putstr(0, s);
			if(on==1){
//				gpio_clr(PTTJ,PIN4);
				gpio_set(PTTJ, PIN1, SET);
//				gpio_set(PTTJ, PIN2, SET);
//				gpio_clr(PTTJ, PIN6);
//				gpio_clr(PTTJ, PIN7);
//				gpio_clr(PTTC, PIN3);
				on=0;
			}else{
//				gpio_set(PTTJ,PIN4,SET);
				gpio_clr(PTTJ, PIN1);
//				gpio_clr(PTTJ, PIN2);
//				gpio_set(PTTJ, PIN6, SET);
//				gpio_set(PTTJ, PIN7, SET);
//				gpio_set(PTTC, PIN3, SET);
				on=1;
			}
		}
	}


//	if(g_counter > 1000){
//		
//		if(on==1){
//			gpio_clr(PTTJ,PIN4);
//			on=0;
//		}else{
//			gpio_set(PTTJ,PIN4,SET);
//			on=1;
//		}
//		
//		delay_ms(1000);
//	}


}
