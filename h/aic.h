//----------------------------------------------------------------------------
// File Name           : aic.h
// Object              : Advanced Interrupt Controller Definition File.
//
// 1.0 27/10/02 GR     : Creation
//----------------------------------------------------------------------------

#ifndef aic_h
#define aic_h

#include "std_c.h"

/*-----------------------------------------*/
/* AIC User Interface Structure Definition */
/*-----------------------------------------*/

typedef struct {
   at91_reg AIC_SMR[32]; /* Source Mode Register */
   at91_reg AIC_SVR[32]; /* Source Vector Register */
   at91_reg AIC_IVR; /* IRQ Vector Register */
   at91_reg AIC_FVR; /* FIQ Vector Register */
   at91_reg AIC_ISR; /* Interrupt Status Register */
   at91_reg AIC_IPR; /* Interrupt Pending Register */
   at91_reg AIC_IMR; /* Interrupt Mask Register */
   at91_reg AIC_CISR; /* Core Interrupt Status Register */
   at91_reg reserved0;
   at91_reg reserved1;
   at91_reg AIC_IECR; /* Interrupt Enable Command Register */
   at91_reg AIC_IDCR; /* Interrupt Disable Command Register */
   at91_reg AIC_ICCR; /* Interrupt Clear Command Register */
   at91_reg AIC_ISCR; /* Interrupt Set Command Register */
   at91_reg AIC_EOICR; /* End of Interrupt Command Register */
   at91_reg AIC_SPU; /* Spurious Vector Register */
} StructAIC;

/*--------------------------------------------*/
/* AIC_SMR[]: Interrupt Source Mode Registers */
/*--------------------------------------------*/

#define AIC_PRIOR 0x07 /* Priority */

#define AIC_SRCTYPE 0x60 /* Source Type Definition */

/* Internal Interrupts */
#define AIC_SRCTYPE_INT_LEVEL_SENSITIVE 0x00 /* Level Sensitive */
#define AIC_SRCTYPE_INT_EDGE_TRIGGERED 0x20 /* Edge Triggered */

/* External Interrupts */
#define AIC_SRCTYPE_EXT_LOW_LEVEL 0x00 /* Low Level */
#define AIC_SRCTYPE_EXT_NEGATIVE_EDGE 0x20 /* Negative Edge */
#define AIC_SRCTYPE_EXT_HIGH_LEVEL 0x40 /* High Level */
#define AIC_SRCTYPE_EXT_POSITIVE_EDGE 0x60 /* Positive Edge */

/*------------------------------------*/
/* AIC_ISR: Interrupt Status Register */
/*------------------------------------*/

#define AIC_IRQID 0x1F /* Current source interrupt */

/*------------------------------------------*/
/* AIC_CISR: Interrupt Core Status Register */
/*------------------------------------------*/

#define AIC_NFIQ 0x01 /* Core FIQ Status */
#define AIC_NIRQ 0x02 /* Core IRQ Status */

/*-------------------------------------*/
/* Peripheral and Interrupt Identifier */
/*-------------------------------------*/

#define FIQ_ID 0 /* Fast Interrupt */
#define SWIRQ_ID 1 /* Soft Interrupt (generated by the AIC) */
#define US0_ID 2 /* USART Channel 0 */
#define US1_ID 3 /* USART Channel 1 */
#define US2_ID 4 /* USART Channel 2 */
#define SPI_ID 5 /* SPI */
#define TC0_ID 6 /* Timer Channel 0 */
#define TC1_ID 7 /* Timer Channel 1 */
#define TC2_ID 8 /* Timer Channel 2 */
#define TC3_ID 9 /* Timer Channel 3 */
#define TC4_ID 10 /* Timer Channel 4 */
#define TC5_ID 11 /* Timer Channel 5 */
#define WD_ID 12 /* Watchdog */
#define PIOA_ID 13 /* Parallel I/O Controller A */
#define PIOB_ID 14 /* Parallel I/O Controller B */

#define IRQ3_ID 28 /* External interrupt 3 */
#define IRQ2_ID 29 /* External interrupt 2 */
#define IRQ1_ID 30 /* External interrupt 1 */
#define IRQ0_ID 31 /* External interrupt 0 */

/*-------------------------------*/
/* Advanced Interrupt Controller */
/*-------------------------------*/

#define AIC_BASE ((StructAIC*)0xFFFFF000)

#endif /* aic_h */
