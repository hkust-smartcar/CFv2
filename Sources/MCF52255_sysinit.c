/*
 * File:		mcf52255_sysinit.c
 * Purpose:		Reset configuration of the MCF52255
 *
 * Notes:
 */
#include <cstdint>
#include "support_common.h"
#include "exceptions.h"
extern uint32 VECTOR_TABLE[];
//extern uint32 __VECTOR_RAM[];

/********************************************************************/
void
pll_init(void)
{
//	uint8_t fref = 8;
//	uint8_t cchr = 0x00;
//	uint8_t mfd = 4;
//	g_pll_clk = (uint32_t) ((fref/(cchr+1)) * 2 * (mfd + 2) * 1000);
	
	MCF_CLOCK_CCHR = 0x00; // The PLL pre divider - 8MHz / 1 = 8MHz 

	//Multiplication Factor Divider - MFD
	//Reduced frequency divider field - RFD
	//fsys = fref * 2(MFD + 2)/2^(RFD);
	//fref * 2(MFD + 2) <= (Max_Spec)MHz
	//fsys <= (Max_Spec) MHz
	
    MCF_CLOCK_SYNCR = MCF_CLOCK_SYNCR_MFD(3) | MCF_CLOCK_SYNCR_RFD(0) | MCF_CLOCK_SYNCR_CLKSRC| MCF_CLOCK_SYNCR_PLLMODE | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))
    {
    }
}
/********************************************************************/
void
scm_init(void)
{
	/*
	 * Enable on-chip modules to access internal SRAM
	 */
	MCF_SCM_RAMBAR = (0
		| MCF_SCM_RAMBAR_BA(RAMBAR_ADDRESS)
		| MCF_SCM_RAMBAR_BDE);
}
/********************************************************************/
void __initialize_hardware(void)
{
	/*******************************************************
	*	Out of reset, the low-level assembly code calls this 
	*	routine to initialize the MCF52255 modules.
	********************************************************/

	asm 
	{
	    /* Initialize IPSBAR */
	    move.l  #__IPSBAR,d0
	       andi.l  #0xC0000000,d0 // need to mask
	    add.l   #0x1,d0
	    move.l  d0,0x40000000

	    

	    /* Initialize FLASHBAR */
	    move.l  #__FLASHBAR,d0
	       andi.l  #0xFFF80000,d0 // need to mask
	    add.l   #0x61,d0
	    movec   d0,FLASHBAR

	}
   	
	
	pll_init();
	scm_init();	

	initialize_exceptions();
}
