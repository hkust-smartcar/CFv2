/*
 * tsl1401.c
 *
 *  Created on: Jan 28, 2015
 *      Author: Harrison
 */

#include "tsl1401.h"
#include "delay.h"
#include "adc.h"
#include "gpio.h"

uint32 CCD[128];

#define CCD_CLK  MCF_GPIO_PORTAN_PORTAN7
#define CCD_SI  MCF_GPIO_PORTAN_PORTAN2

#define CCD_CLK_1 MCF_GPIO_PORTAN|=CCD_CLK	
#define CCD_SI_1 MCF_GPIO_PORTAN|=CCD_SI

#define CCD_CLK_0 MCF_GPIO_PORTAN&=~CCD_CLK	
#define CCD_SI_0 MCF_GPIO_PORTAN&=~CCD_SI


uint16 MAX=0,MIN=0xffff;
uint32 AVG=0;
uint32 ALL = 0;

void tsl1401_init(){
	ADC_init(PIN5);
	gpio_init(PTAN, PIN7, GPIO, OUT, CLR);
	gpio_init(PTAN, PIN2, GPIO, OUT, CLR);
}

void tsl1401_collect(void)
{   
    MAX=0;
    MIN=0xffff;
    AVG=0;
    ALL = 0;
    CCD_SI_1;
    delay_us(5);
    CCD_CLK_1;   
    delay_us(5);
    CCD_SI_0; 
    delay_us(5);
    
    for(int i=0;i<128;i++)    //128个光点周期
    {
       CCD_CLK_0;
       delay_us(12);
       CCD[i]=(uint32) ADonce(PIN5) * 33 / 10 / 4096;     //采集单个点数据
       ALL += CCD[i];
       CCD_CLK_1;
       delay_us(12);
       
//       AVG+=CCD[i];
	   if(CCD[i]>MAX)MAX=CCD[i]; 
	   if(CCD[i]<MIN)MIN=CCD[i]; 
    }
    
    AVG=ALL/128;

    CCD_CLK_0;   //clk=0    
}

uint32* GetCCD(){
	return CCD;
}

uint32 GetCCDAvg(){
	return AVG;
}
