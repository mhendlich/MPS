//----------------------------------------------------------------------------
// File Name           : pmc.h
// Object              : Power Management Controller Header File.
//
// 1.0 27/10/02 GR     : Creation
//----------------------------------------------------------------------------
#ifndef pmc_h
#define pmc_h

#include "std_c.h"

/*--------------------------------------------------*/
/* Power Management Controller Structure Definition */
/*--------------------------------------------------*/

typedef struct
{
    at91_reg    PMC_SCER ;  /* System Clock Enable  Register */
    at91_reg    PMC_SCDR ;  /* System Clock Disable Register */
    at91_reg    PMC_SCSR ;  /* System Clock Status  Register */
    at91_reg    Reserved0 ;
    at91_reg    PMC_PCER ;  /* Peripheral Clock Enable  Register */
    at91_reg    PMC_PCDR ;  /* Peripheral Clock Disable Register */
    at91_reg    PMC_PCSR ;  /* Peripheral Clock Status  Register */
} StructPMC ;

/*-----------------------------------------------*/
/* Power Saving Control Register Bits Definition */
/*-----------------------------------------------*/
    
#define PMC_ARM7DIS         0x1
#define PMC_US0             0x4
#define PMC_PCSR_ALL        0xffff

/*------------------------------------------*/ 
/* Power Management Controller Base Address */
/*------------------------------------------*/ 

#define PMC_BASE        (( StructPMC *) 0xFFFF4000)


#endif /* pmc_h */
