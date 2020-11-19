@*-----------------------------------------------------------------------------
@* File Name           : usart.inc
@* Object              : USART Header File.
@*
@* 1.0 01/04/00	: Creation
@*----------------------------------------------------------------------------

#ifndef usart_inc
#define usart_inc


@-------------------------------------------
@ USART User Interface Structure Definition 
@-------------------------------------------
	
US_CR = 0x0         @ Control Register 
US_MR = 0x4         @ Mode Register 
US_IER = 0x8        @ Interrupt Enable Register 
US_IDR = 0xc        @ Interrupt Disable Register 
US_IMR = 0x10        @ Interrupt Mask Register 
US_CSR = 0x14        @ Channel Status Register 
US_RHR = 0x18        @ Receive Holding Register 
US_THR = 0x1c        @ Transmit Holding Register 
US_BRGR = 0x20       @ Baud Rate Generator Register 
US_RTOR = 0x24       @ Receiver Timeout Register 
US_TTGR = 0x28       @ Transmitter Time-guard Register 
   @      Reserved 
US_RPR = 0x30        @ Receiver Pointer Register 
US_RCR = 0x34        @ Receiver Counter Register 
US_TPR = 0x38        @ Transmitter Pointer Register 
US_TCR = 0x3c        @ Transmitter Counter Register 

@--------------------------
@ US_CR : Control Register 
@--------------------------

US_RSTRX	=	0x0004      @ Reset Receiver 
US_RSTTX	=	0x0008      @ Reset Transmitter 
US_RXEN		=	0x0010      @ Receiver Enable 
US_RXDIS	=	0x0020      @ Receiver Disable 
US_TXEN		=	0x0040      @ Transmitter Enable 
US_TXDIS	=	0x0080      @ Transmitter Disable 
US_RSTSTA	=	0x0100      @ Reset Status Bits 
US_STTBRK	=	0x0200      @ Start Break 
US_STPBRK	=	0x0400      @ Stop Break 
US_STTTO	=	0x0800      @ Start Time-out 
US_SENDA	=	0x1000      @ Send Address 

@-----------------------
@ US_MR : Mode Register 
@-----------------------

US_CLKS         =        0x0030      @ Clock Selection 
US_CLKS_MCK     =        0x00        @ Master Clock 
US_CLKS_MCK8    =        0x10        @ Master Clock divided by 8 
US_CLKS_SCK     =        0x20        @ External Clock 
US_CLKS_SLCK    =        0x30        @ Slow Clock 

US_CHRL         =        0x00C0      @ Byte Length 
US_CHRL_5       =        0x00        @ 5 bits 
US_CHRL_6       =        0x40        @ 6 bits 
US_CHRL_7       =        0x80        @ 7 bits 
US_CHRL_8       =        0xC0        @ 8 bits 

US_SYNC         =        0x0100      @ Synchronous Mode Enable 

US_PAR          =        0x0E00      @ Parity Mode 
US_PAR_EVEN     =        0x00        @ Even Parity 
US_PAR_ODD      =        0x200       @ Odd Parity 
US_PAR_SPACE    =        0x400       @ Space Parity to 0 
US_PAR_MARK     =        0x600       @ Marked Parity to 1 
US_PAR_NO       =        0x800       @ No Parity 
US_PAR_MULTIDROP =       0xC00       @ Multi-drop Mode 

US_NBSTOP        =       0x3000      @ Stop Bit Number 
US_NBSTOP_1      =       0x0000      @ 1 Stop Bit 
US_NBSTOP_1_5    =       0x1000      @ 1.5 Stop Bits 
US_NBSTOP_2      =       0x2000      @ 2 Stop Bits 

US_CHMODE                =   0xC000  @ Channel Mode 
US_CHMODE_NORMAL         =   0x0000  @ Normal Mode 
US_CHMODE_AUTOMATIC_ECHO =   0x4000  @ Automatic Echo 
US_CHMODE_LOCAL_LOOPBACK =   0x8000  @ Local Loopback 
US_CHMODE_REMOTE_LOOPBACK =  0xC000  @ Remote Loopback 

US_MODE9        =        0x20000     @ 9 Bit Mode 

US_CLKO         =        0x40000     @ Baud Rate Output Enable 


@---------------------------------------------------------------
@ US_IER, US_IDR, US_IMR, US_IMR: Status and Interrupt Register 
@---------------------------------------------------------------

US_RXRDY       =     0x001       @ Receiver Ready 
US_TXRDY       =     0x002       @ Transmitter Ready 
US_RXBRK       =     0x004       @ Receiver Break 
US_ENDRX       =     0x008       @ End of Receiver PDC Transfer 
US_ENDTX       =     0x010       @ End of Transmitter PDC Transfer 
US_OVRE        =     0x020       @ Overrun Error 
US_FRAME       =     0x040       @ Framing Error 
US_PARE        =     0x080       @ Parity Error 
US_TIMEOUT     =     0x100       @ Receiver Timeout 
US_TXEMPTY     =     0x200       @ Transmitter Empty 

US_MASK_IRQ_TX    =  (US_TXRDY | US_ENDTX | US_TXEMPTY)
US_MASK_IRQ_RX    =  (US_RXRDY | US_ENDRX | US_TIMEOUT)
US_MASK_IRQ_ERROR =  (US_PARE | US_FRAME | US_OVRE | US_RXBRK)


USART2_BASE  =   0xFFFC8000      @ USART 2 
USART1_BASE  =   0xFFFC4000      @ USART 1 
USART0_BASE  =   0xFFFC0000      @ USART 0 

#endif 
