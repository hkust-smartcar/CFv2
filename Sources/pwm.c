
/*
 * File:    pwm.c
 * Purpose: Source for the Pulse Width Modulation Module
 * 
 * License:     All software covered by license agreement in -
 *              docs/Freescale_Software_License.pdf
 */
#include "support_common.h"
#include "stdio.h"
#include "lcd.h"
#include "pwm.h"

uint8 shutdown = 0;

/*
*	PWM Initialization for module u8PWMModule
*
*/
int8 PWMInit(PWMInfo pwminfo, uint8 u8PWMModule)
{

	/*Clock A = Internal Bus Clock / 2^Prescaler
	Clock SA = Clock A / (2 * PWMSCLA)
	PWMFrequency = Clock(A,B,SA, or SB) / PWMPERn
	Duty Cycle = (1 - PWMPOL[PPOLn] - PWMDTYn/PWMPERn) * 100
	*/
	//GPIO setting for PWM, polarity setting, input clock and alignment setting
	switch(u8PWMModule)
	{
	case 0:		
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL0;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL0;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK0;	//select SA
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK0;//select A
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE0;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE0;
		break;
	case 2:	
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL2;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL2;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK2;	//select SB
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK2;//select B
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE2;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE2;
		break;
	case 4:
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL4;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL4;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK4;	//select SA
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK4;//select A
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE4;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE4;
		break;
	case 6:
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL6;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL6;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK6;	//select SB
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK6;//select B
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE6;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE6;
		break;
	case 1:		
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL1;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL1;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK1;	//select SA
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK1;//select A
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE1;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE1;
		break;
	case 3:	
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL3;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL3;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK3;	//select SB
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK3;//select B
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE3;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE3;
		break;
	case 5:		
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL5;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL5;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK5;	//select SA
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK5;//select A
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE5;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE5;
		break;
	case 7:	
		if(pwminfo.u8Polarity)
			MCF_PWM_PWMPOL |= MCF_PWM_PWMPOL_PPOL7;
		else
			MCF_PWM_PWMPOL &= ~MCF_PWM_PWMPOL_PPOL7;
		if(pwminfo.u8Clksel)
			MCF_PWM_PWMCLK |= MCF_PWM_PWMCLK_PCLK7;	//select SB
		else
			MCF_PWM_PWMCLK &= ~MCF_PWM_PWMCLK_PCLK7;//select B
		if(pwminfo.u8ALign)
			MCF_PWM_PWMCAE |= MCF_PWM_PWMCAE_CAE7;
		else
			MCF_PWM_PWMCAE &= ~MCF_PWM_PWMCAE_CAE7;
		break;
	default:
		break;
	}
	
	//Prescaler for clock A and B
	MCF_PWM_PWMPRCLK = MCF_PWM_PWMPRCLK_PCKA(pwminfo.u8PrescalerA)| MCF_PWM_PWMPRCLK_PCKB(pwminfo.u8PrescalerB);

	//Divisor from clock SA to A and SB to B
	MCF_PWM_PWMSCLA = MCF_PWM_PWMSCLA_SCALEA(pwminfo.u8SADivisor);
	MCF_PWM_PWMSCLB = MCF_PWM_PWMSCLB_SCALEB(pwminfo.u8SBDivisor);
		
	//set PWM period
	MCF_PWM_PWMPER(u8PWMModule) = MCF_PWM_PWMPER_PERIOD(pwminfo.u8Period);
	
	//set PWM duty cycle
	MCF_PWM_PWMDTY(u8PWMModule) = MCF_PWM_PWMDTY_DUTY(pwminfo.u8Duty);

	if((pwminfo.u8Concat&0x01) == 0x01)
		//channel 0 and 1 as 16bit mode
		MCF_PWM_PWMCTL |= MCF_PWM_PWMCTL_CON01;
	if((pwminfo.u8Concat&0x02) == 0x02)
		//channel 2 and 3 as 16bit mode
		MCF_PWM_PWMCTL |= MCF_PWM_PWMCTL_CON23;
	if((pwminfo.u8Concat&0x04) == 0x04)
		//channel 4 and 5 as 16bit mode
		MCF_PWM_PWMCTL |= MCF_PWM_PWMCTL_CON45;
	if((pwminfo.u8Concat&0x08) == 0x08)
		//channel 6 and 7 as 16bit mode
		MCF_PWM_PWMCTL |= MCF_PWM_PWMCTL_CON67;

	if(pwminfo.u8StopInDoze)
		MCF_PWM_PWMCTL |= MCF_PWM_PWMCTL_PSWAI;
	else
		MCF_PWM_PWMCTL &= ~MCF_PWM_PWMCTL_PSWAI;
	if(pwminfo.u8StopInDebug)
		MCF_PWM_PWMCTL |= MCF_PWM_PWMCTL_PFRZ;
	else
		MCF_PWM_PWMCTL &= ~MCF_PWM_PWMCTL_PFRZ;

#if 1	
	char s[100];
	sprintf(s,"PRCLK is 0x%x\n",MCF_PWM_PWMPRCLK);
	LcdDrawString(0, 2*FONT_H, s, 0xFFF0,0x0000);
	sprintf(s,"SCLA is 0x%x\n",MCF_PWM_PWMSCLA);
	LcdDrawString(0, 3*FONT_H, s, 0xFFF0,0x0000);
	sprintf(s,"SCLB is 0x%x\n",MCF_PWM_PWMSCLB);
	LcdDrawString(0, 4*FONT_H, s, 0xFFF0,0x0000);
	sprintf(s,"PER is 0x%x\n",MCF_PWM_PWMPER(u8PWMModule) );
	LcdDrawString(0, 5*FONT_H, s, 0xFFF0,0x0000);
	sprintf(s,"CLK is 0x%x\n", MCF_PWM_PWMCLK);
	LcdDrawString(0, 6*FONT_H, s, 0xFFF0,0x0000);
	sprintf(s,"CAE is 0x%x\n", MCF_PWM_PWMCAE);
	LcdDrawString(0, 7*FONT_H, s, 0xFFF0,0x0000);
	sprintf(s,"CTL is 0x%x\n",MCF_PWM_PWMCTL);
	LcdDrawString(0, 8*FONT_H, s, 0xFFF0,0x0000);
#endif

	return 0;
}

void PWMEnable(uint8 u8PWMModule)
{
	MCF_PWM_PWME |= (0x01 << u8PWMModule);
}

void PWMDisable(uint8 u8PWMModule)
{
	MCF_PWM_PWME &= ~(0x01 << u8PWMModule);
}

void PWMShutdown(void)
{	
	//unmask PWM interrupts in INTC0
	MCF_INTC0_IMRH &= ~(MCF_INTC_IMRH_INT_MASK52 | MCF_INTC_IMRL_MASKALL);
        
    /* Setup the interrupt level and priority for UART0 */
	MCF_INTC0_ICR52 = MCF_INTC_ICR_IL(3) | MCF_INTC_ICR_IP(4);
	
 	/* Set the interrupt handlers in the vector table */
//	mcf5xxx_set_handler(64 + 52, (ADDRESS)pwm_handler);	
	__VECTOR_RAM[64+52] = (uint32) pwm_handler;
	
	MCF_PWM_PWMSDN |= MCF_PWM_PWMSDN_IE;	//interrupt enable when PWM7IN changed
//	MCF_PWM_PWMSDN |= MCF_PWM_PWMSDN_LVL;	//force PWM shutdown level to high
	MCF_PWM_PWMSDN |= MCF_PWM_PWMSDN_PWM7IL;	//PWM7 input is active high
	
	MCF_PWM_PWMSDN |= MCF_PWM_PWMSDN_SDNEN;	//enable emergency shutdown
}

void PWMExitShutdown(void)
{
	MCF_INTC0_IMRH |= MCF_INTC_IMRH_INT_MASK52;	//mask PWM interrupt
	MCF_PWM_PWMSDN &= ~MCF_PWM_PWMSDN_IE;	//interrupt enable when PWM7IN changed
	MCF_PWM_PWMSDN &= ~MCF_PWM_PWMSDN_SDNEN;	//enable emergency shutdown
}

void PWMRestart(void)
{
	MCF_PWM_PWMSDN |= MCF_PWM_PWMSDN_RESTART;
}

__interrupt__ void pwm_handler(void)
{
	MCF_PWM_PWMSDN |= MCF_PWM_PWMSDN_IF;	
	shutdown = 1;
}
