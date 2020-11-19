@----------------------------------------------------------------------------
@ File Name           : pmc.inc
@ Object              : Power Management Controller Header File.
@
@ 1.0 27/10/02 GR     : Creation
@----------------------------------------------------------------------------
#ifndef pmc_inc
#define pmc_inc

@--------------------------------------------------
@ Power Management Controller Structure Definition 
@--------------------------------------------------

PMC_SCER = 0x0  @ System Clock Enable  Register 
PMC_SCDR = 0x4  @ System Clock Disable Register 
PMC_SCSR = 0x8  @ System Clock Status  Register 
@ Reserved 
PMC_PCER = 0x10  @ Peripheral Clock Enable  Register 
PMC_PCDR = 0x14  @ Peripheral Clock Disable Register 
PMC_PCSR = 0x18  @ Peripheral Clock Status  Register 

@-----------------------------------------------
@ Power Saving Control Register Bits Definition 
@-----------------------------------------------
    
PMC_ARM7DIS = 0x1
PMC_US0 = (1<<2)
PMC_US1 = (1<<3)
PMC_US2 = (1<<4)
PMC_TC0 = (1<<6)		
PMC_TC1 = (1<<7)		
PMC_TC2 = (1<<8)		
PMC_TC3 = (1<<9)		
PMC_TC4 = (1<<10)		
PMC_TC5 = (1<<11)		
PMC_PIOA = (1<<13)
PMC_PIOB = (1<<14)
PMC_PCSR_ALL = 0xffff

@------------------------------------------ 
@ Power Management Controller Base Address 
@------------------------------------------ 

PMC_BASE = 0xFFFF4000


#endif 
