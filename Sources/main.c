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


/*volatile uint32_t g_counter = 0;
__interrupt__
void pit_isr_handler(){
    MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
	g_counter++;
}*/
char* s;
extern uint16_t* g_omega;
/*
void pit0_init() {
	// Clear the enable bit so we can configure the timer
	MCF_PIT0_PCSR &= ~(MCF_PIT_PCSR_EN);
	
	// Write a prescaler of 1 which generates an interrupt every 3ms seconds
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PRE(0x05);
	
	// Timer will stop when execution is halted by the debugger
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_DBG;
	
	// Allow overwriting over the PIT counter
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_OVW;
	
	// Enable interrupts from PIT0
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIE;
	
	// Clear interrupt flag by writing a 1
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
	
	// When PCNTR0 reaches 0, it is reloaded
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_RLD;
	
	// Write 0 into PIT Modulus register (which will reset it to 0xFFFF)
	MCF_PIT0_PMR = MCF_PIT_PMR_PM(0);
	
	// Interrupt Controller: PIT0 interrupts as level 4 priority 7 (Source 55)
	MCF_INTC0_ICR55 |= MCF_INTC_ICR_IL(0x04);
	MCF_INTC0_ICR55 |= MCF_INTC_ICR_IP(0x07);
	
	// Unmask interrupts from the interrupt source
	MCF_INTC0_IMRH &= ~(1 << (55 - 32));
	
	// Write PIT0 ISR address into the exception vector table (at position 64+55)
	__VECTOR_RAM[64+55] = (uint32)pit_isr_handler;
	
	g_counter = 0;
	
	// Enable timer
	MCF_PIT0_PCSR |= MCF_PIT_PCSR_EN;
}*/

int main(void)
{
	int on = 1;
	uint8 whoami;
	int8 result;
	char s_[100];
	char* data;
	uint8 d,d2;
	int i;
//	g_counter = 0;
	s = s_;
	
	/*GPIO tests*/
	//Config PortTJ4 as GPIO
//	gpio_init(PTTJ, PIN4, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN0, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN7, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN1, GPIO, OUT, CLR);
//	gpio_init(PTTJ, PIN6, GPIO, OUT, CLR);
	/*GPIO tests*/
	
	
//	delay_ms(500);
	/*uart tests*/
	uart_init(1,SYSTEM_CLOCK_KHZ,115200);
//	printf("Hello World in C++ from MCF52255 derivative on MCF52255 board\n\r");
	
	/*uart tests*/
//	delay_ms(1000);
//	result = QSPIInit(15000,0,8,0,0,1);
//	LcdInit();
//	uint8_t *state = (uint8_t*)malloc(1);
//	i2c_rx(MPU6050_DEFAULT_ADDRESS, 1, state, 150);
//	d2 = I2CreceiveByte(MPU6050_RA_TEMP_OUT_L, MPU6050_DEFAULT_ADDRESS);
//	sprintf(s,"i2c: %d %d %d\n",state[0],state[1],state[2]);
//	LcdClear(0x0000);
		
	//PITInit(5, 0x1FF, 0);
	//PIT_EnableInts(pit_isr_handler, 0);
	//PIT_Start(0);
//	pit0_init();
//	g_counter = 1;
	
	//MCF_INTC0_INTFRCH |= MCF_INTC_INTFRCH_INTFRC55;

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
//	I2CInit();
//	char * s;
	mpu6050_init();
	delay_ms(2);
	uint8_t wai = I2CReadByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I);
//	sprintf(s, "who am i: %d\n", wai);
//	uart_putstr(1,s);
	uart_putchar(1,wai);
	uart_putchar(1,'\n');
	mpu6050_update();
//	printf("temp: %d\n", (int)GetTemp());
	uint16_t* omega;
	uint16_t* accel;
	while (1)
	{
		
		mpu6050_update();
		omega = GetOmega();
		accel = GetAccel();
//		uart_putchar(1,GetTemp());
//		uart_putchar(1,'\n');
		sprintf(s, "%d %d %d %d %d %d %d\n", accel[0], accel[1], accel[2], omega[0], omega[1], omega[2], (int)GetTemp());
		uart_putstr(1,s);
		delay_ms(1000);
		/*
	if(g_counter > 1000){
//		LcdDrawString(0, 16, "CCD1\0", 0xFFF0,0x0000);
//		LcdDrawString(0, 32, "CCD2\0", 0xFFF0,0x0000);
		if(on==1){
			gpio_clr(PTTJ,PIN4);
			on=0;
		}else{
			gpio_set(PTTJ,PIN4,SET);
			on=1;
		}
		
	}*/
	}
#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)
//	printf("Hello World in C++ from MCF52255 derivative on MCF52255 board\n\r");
#endif
//	for(;;) {	   
//	   	counter++;
//	}
}
