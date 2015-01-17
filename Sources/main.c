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


volatile uint32_t g_counter = 0;
__interrupt__
void pit_isr_handler(){
    MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
	g_counter++;
	g_counter%=1000;
	char s[20];
	sprintf(s, "%d\n", g_counter);
	uart_putstr(1,s);
}

char* s;
extern uint16_t* g_omega;

int main(void)
{
	int on = 1;
	g_counter = 0;
	
	/*GPIO tests*/
	gpio_init(PTTJ, PIN4, GPIO, OUT, CLR);
	/*GPIO tests*/
	
	
	/*uart tests*/
	uart_init(1,SYSTEM_CLOCK_KHZ,115200);
	
	/*uart tests*/
//	LcdInit();
//	LcdClear(0x0000);
//		LcdDrawString(0, 32, "CCD2\0", 0xFFF0,0x0000);

//	qspi_init(QSPI0, Q_MODE0, 1000000L);
		
	PITInit(0);
	PIT_EnableInts(pit_isr_handler, 0);
	PIT_Start(0);



	while(1){
		if(g_counter%1000==0){
			if(on==1){
				gpio_clr(PTTJ,PIN4);
				on=0;
			}else{
				gpio_set(PTTJ,PIN4,SET);
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
