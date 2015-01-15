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
}

char* s;
extern uint16_t* g_omega;

int main(void)
{
	int on = 1;
	uint8 whoami;
	int8 result;
	char s_[100];
	char* data;
	uint8 d,d2;
	int i;
	g_counter = 0;
	s = s_;
	
	/*GPIO tests*/
	//Config PortTJ4 as GPIO
	gpio_init(PTTJ, PIN4, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN0, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN7, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN1, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN6, GPIO, OUT, CLR);
	/*GPIO tests*/
	
	
	/*uart tests*/
	uart_init(1,SYSTEM_CLOCK_KHZ,115200);
	
	/*uart tests*/
//	delay_ms(1000);
//	LcdInit();
//	LcdClear(0x0000);
	
		
	PITInit(5, 0x1FF, 0);
	PIT_EnableInts(pit_isr_handler, 0);
	PIT_Start(0);
	//pit0_init();
	g_counter = 1;
	
	//MCF_INTC0_INTFRCH |= MCF_INTC_INTFRCH_INTFRC55;

	for (int i = 0; i < 10000000; ++i)
	{
		asm("nop");
	}
	//delay_ms(100);
	/*delay_ms(100);
	sprintf(s, "\npcsr: %d\n", MCF_PIT0_PCSR);
	uart_putstr(1,s);
	sprintf(s, "pmr: %d\n", MCF_PIT0_PMR);
	uart_putstr(1,s);
	sprintf(s, "cnt: %d\n", MCF_PIT0_PCNTR);
	uart_putstr(1,s);
	delay_ms(100);
	
	 * pit: working
	 * interrupt calling isr: working
	 * pit interrupt request: working
	 * pit interrupt calling isr: not working
	 * 
	 * that format error shit proved that isr is working, not hw problem \(^0^)/...
	 
	sprintf(s, "var: %d\n", g_counter);
	uart_putstr(1,s);
	//__VECTOR_RAM[INT_PIT0_PIF]();
	sprintf(s, "var: %d\n", g_counter);
	uart_putstr(1,s);
	sprintf(s, "imrh: %d\n", MCF_INTC0_IMRH);
	uart_putstr(1,s);
	sprintf(s, "imrl: %d\n", MCF_INTC0_IMRL);
	uart_putstr(1,s);
	sprintf(s, "iprh: %d\n", MCF_INTC0_IPRH);
	uart_putstr(1,s);
	sprintf(s, "iprl: %d\n", MCF_INTC0_IPRL);
	uart_putstr(1,s);
	sprintf(s, "irlr: %d\n", MCF_INTC0_IRLR);
	uart_putstr(1,s);
	delay_ms(100);*/

//	mpu6050_init();
//	delay_ms(2);
//	uint8_t wai = I2CReadByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I);
//	uart_putchar(1,wai);
//	uart_putchar(1,'\n');
//	mpu6050_update();

//	uint16_t* omega;
//	uint16_t* accel;
	int state = 1;
	//delay_ms(100);
	//qspi_init(QSPI0, Q_MODE0, 1000000L);
	while (1)
	{
		//state = !state;
		//LcdDrawString(0, 16, "CCD1\0", 0xFFF0,0x0000);
//		uint8 i = qspi_read_data(QSPI0, 0x23);
//		char ch[128];
//		sprintf(ch, "%x", i);
//		uart_putstr(1,ch);
//		delay_ms(100);
//		mpu6050_update();
//		omega = GetOmega();
//		accel = GetAccel();
//		uart_putchar(1,GetTemp());
//		uart_putchar(1,'\n');
//		sprintf(s, "%d %d %d %d %d %d %d\n", accel[0], accel[1], accel[2], omega[0], omega[1], omega[2], GetTemp());
//		uart_putstr(1,s);
//		delay_ms(1000);

	if(g_counter > 1000){
		
//		LcdDrawString(0, 32, "CCD2\0", 0xFFF0,0x0000);
		if(on==1){
			gpio_clr(PTTJ,PIN4);
			on=0;
		}else{
			gpio_set(PTTJ,PIN4,SET);
			on=1;
		}
		
		for (int i = 0; i < 5000000; ++i)
		{
			asm("nop");
		}
	}
	}
#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)
//	printf("Hello World in C++ from MCF52255 derivative on MCF52255 board\n\r");
#endif
//	for(;;) {	   
//	   	counter++;
//	}
}
