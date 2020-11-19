@----------------------------------------------------------------------------
@ File Name           : ebi.inc
@ Object              : Power Management Controller Header File.
@
@ 1.0 27/10/02 GR     : Creation
@----------------------------------------------------------------------------

#ifndef ebi_inc
#define ebi_inc

@------------------------------------------------------------------------------
@- EBI Initialization Data
@-------------------------
@- The EBI values depend to target choice , Clock, and memories access time.
@- Yous must be define these values in include file
@- The EBI User Interface Image which is copied by the boot.
@- The EBI_CSR_x are defined in the target and hardware depend.
@- That's hardware! Details in the Electrical Datasheet of the AT91 device.
@- EBI Base Address is added at the end for commodity in copy code.
@- ICE note :For ICE debug no need to set the EBI value these values already set
@- by the boot function.
@------------------------------------------------------------------------------
FLASH_BASE	=	0x1000000
EXT_SRAM_BASE	=	0x2000000
EBI_BASE        =     0xFFE00000      @- External Bus Interface

EBI_CSR_0   	=     (FLASH_BASE  |  0x2529)    @ 0x01000000, 16MB, 2 tdf, 16 bits, 2 WS
EBI_CSR_1   	=     (EXT_SRAM_BASE  |  0x2121) @ 0x02000000, 16MB, 0 hold, 16 bits, 1 WS
EBI_CSR_2   	=     0x20000000  @ unused
EBI_CSR_3   	=     0x30000000  @ unused
EBI_CSR_4   	=     0x40000000  @ unused
EBI_CSR_5   	=     0x50000000  @ unused
EBI_CSR_6   	=     0x60000000  @ unused
EBI_CSR_7   	=     0x70000000  @ unused

#endif 
