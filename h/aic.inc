@----------------------------------------------------------------------------
@ File Name           : aic.inc
@ Object              : Advanced Interrupt Controller Header File.
@
@ 1.0 27/20/02 GR    : Creation
@----------------------------------------------------------------------------

#ifndef aic_inc
#define aic_inc

@------------------------------------------
@- AIC User Interface Structure Definition
@------------------------------------------

AIC_SMR             =       0		@- Source Mode Register
AIC_SVR             =       0x80        @- Source Vector Register
AIC_IVR             =       0x100       @- IRQ Vector Register
AIC_FVR             =       0x104	@- FIQ Vector Register
AIC_ISR             =       0x108       @- Interrupt Status Register
AIC_IPR             =       0x10c       @- Interrupt Pending Register
AIC_IMR             =       0x110       @- Interrupt Mask Register
AIC_CISR            =       0x114       @- Core Interrupt Status Register
@                   =       0x118       @- Reserved 0
@                   =       0x11c       @- Reserved 1
AIC_IECR            =       0x120       @- Interrupt Enable Command Register
AIC_IDCR            =       0x124       @- Interrupt Disable Command Register
AIC_ICCR            =       0x128       @- Interrupt Clear Command Register
AIC_ISCR            =       0x12c       @- Interrupt Set Command Register
AIC_EOICR           =       0x130       @-  of Interrupt Command Register
AIC_SPU             =       0x134       @- Spurious Vector Register

@---------------------------------------------
@- AIC_SMR[]: Interrupt Source Mode Registers
@---------------------------------------------

AIC_PRIOR                       =     0x07    @- Priority

AIC_SRCTYPE                     =     0x60    @- Source Type Definition
AIC_SRCTYPE_INT_LEVEL_SENSITIVE =     0x00    @- Level Sensitive
AIC_SRCTYPE_INT_EDGE_TRIGGERED  =     0x20    @- Edge Triggered
AIC_SRCTYPE_EXT_LOW_LEVEL       =     0x00    @- Low Level
AIC_SRCTYPE_EXT_NEGATIVE_EDGE   =     0x20    @- Negative Edge
AIC_SRCTYPE_EXT_HIGH_LEVEL      =     0x40    @- High Level
AIC_SRCTYPE_EXT_POSITIVE_EDGE   =     0x60    @- Positive Edge

@--------------------------------------
@-  AIC_ISR: Interrupt Status Register
@--------------------------------------

AIC_IRQID               =     0x1F            @- Current source interrupt

@-------------------------------------------
@- AIC_CISR: Interrupt Core Status Register
@-------------------------------------------

AIC_NFIQ                =     0x01            @- Core FIQ Status
AIC_NIRQ                =     0x02            @- Core IRQ Status

@--------------------------------------------
@- Advanced Interrupt COntroller BAse Address
@--------------------------------------------

AIC_BASE                =     0xFFFFF000

#endif 

