#include "adc.h"
#include "gpio.h"

void ADC_init(PINn pin) 
{
	/* Control 1 Register (CTRL1)
	 * STOP0 : 1 Stop mode
	 * SYNC0 : 1 Scan is initiated by a SYNC0 input pulse or a write to the START0 bit
	 * SMODE : 010 Loop sequential
	 * */
	MCF_ADC_CTRL1 = 0b0101000000000010;
	/* Control 2 Register (CTRL2)
	 * Clock Divisor Select. This field controls the divider circuit, which generates the ADC clock by dividing the
	system clock by 2*(DIV+1). DIV must be chosen so the ADC clock does not exceed 5.0 MHz. See Table 30-5
	for a listing of ADC clock frequency based on the value of DIV for several configurations.*/
	MCF_ADC_CTRL2 = 0b0000000000001001;	
	/* Power Control Register (POWER)
	 * PUDELAY : Power-Up Delay. This field determines the number of ADC clock cycles provided to enable an ADC converter
	(after clearing PD0 or PD1) before allowing a scan to start. 
	 * PD2 : 1 Power-down voltage reference circuit is controlled by PD0 and PD1 (default)*/
	MCF_ADC_POWER = 0b0000000010100100;
	/* Voltage Reference Register (CAL)
	 * SEL_VREFH : VRH
	 * SEL_VREFL : VRL
	 * */
	MCF_ADC_CAL &= ~(MCF_ADC_CAL_SEL_VREFH | MCF_ADC_CAL_SEL_VREFL);
//	MCF_GPIO_PANPAR = 0xFFFF;
	gpio_set_func(PTAN, pin, PRIMARY);
	MCF_ADC_CTRL1 &= 0xBFFF;
	while(MCF_ADC_POWER & MCF_ADC_POWER_PSTS0);
	while(MCF_ADC_POWER & MCF_ADC_POWER_PSTS1);
	MCF_ADC_CTRL1 |= 0x2000;
}

uint16 ADonce(PINn pin) 
{
	uint16 result;
	while(MCF_ADC_ADSTAT & (1 << pin) == 0);
	result = (MCF_ADC_ADRSLT(pin) & 0x7FF8) >> 3;
	return result;
}
