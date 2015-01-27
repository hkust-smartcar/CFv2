/*
 * delay.c
 *
 *  Created on: Dec 28, 2014
 *      Author: Harrison
 */
#include "delay.h"
/********************************************************************/
/*
 * Pause for the specified number of micro-seconds.
 * Uses DTIM3 as a timer
 */
void delay_us(int usecs)
{
    /* Enable the DMA Timer 3 */
    MCF_DTIM3_DTRR = (vuint32)(usecs - 1);
    MCF_DTIM3_DTER = MCF_DTIM_DTER_REF;
    MCF_DTIM3_DTMR = 0
        | MCF_DTIM_DTMR_PS(SYSTEM_CLOCK_KHZ/1000)
        | MCF_DTIM_DTMR_FRR
        | MCF_DTIM_DTMR_CLK_DIV1
        | MCF_DTIM_DTMR_RST;

    while ((MCF_DTIM3_DTER & MCF_DTIM_DTER_REF) == 0) 
    {};
    
    /* Disable the timer */
    MCF_DTIM3_DTMR = 0;
}

void delay_ms(int ms){
	delay_us(ms*1000);
}

