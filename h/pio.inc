@----------------------------------------------------------------------------
@ File Name           : pio.inc
@ Object              : Parallel I/O Header File
@
@ 1.0 27/10/02 GR    : Creation
@----------------------------------------------------------------------------

#ifndef pio_inc
#define pio_inc


@------------------------------------------------------------*/
@ User Interface Parallel I/O Interface Structure Definition */
@------------------------------------------------------------*/

PIO_PER = 0x0           @ PIO Enable Register 
PIO_PDR = 0x4           @ PIO Disable Register 
PIO_PSR = 0x8           @ PIO Status Register 
			@ Reserved 0xC
PIO_OER = 0x10           @ Output Enable Register 
PIO_ODR = 0x14           @ Output Disable Register 
PIO_OSR = 0x18           @ Output Status Register 
			@  Reserved 0x1C
PIO_IFER = 0x20          @ Input Filter Enable Register 
PIO_IFDR = 0x24          @ Input Filter Disable Register 
PIO_IFSR = 0x28          @ Input Filter Status Register 
			@  Reserved 0x2C
PIO_SODR = 0x30         @ Set Output Data Register 
PIO_CODR = 0x34         @ Clear Output Data Register 
PIO_ODSR = 0x38         @ Output Data Status Register 
PIO_PDSR = 0x3C         @ Pin Data Status Register 
PIO_IER = 0x40          @ Interrupt Enable Register 
PIO_IDR = 0x44          @ Interrupt Disable Register 
PIO_IMR = 0x48          @ Interrupt Mask Register 
PIO_ISR = 0x4C          @ Interrupt Status Register 
PIO_MDER = 0x50         @ Multi Driver Enable Register 
PIO_MDDR = 0x54         @ Multi Driver Disable Register 
PIO_MDSR = 0x58          @ Multi Driver Status Register 
			@  Reserved 0x5C

PIOB_BASE     = 0xFFFF0000     @ Parallel I/O Controller B 
PIOA_BASE     = 0xFFFEC000      @ Parallel I/O Controller A 

@ PIO Controller A 
PIOTCLK3   =     0         @ Timer 3 Clock signal 
PIOTIOA3   =     1         @ Timer 3 Signal A 
PIOTIOB3   =     2         @ Timer 3 Signal B 
                                   
PIOTCLK4   =     3         @ Timer 4 Clock signal 
PIOTIOA4   =     4         @ Timer 4 Signal A 
PIOTIOB4   =     5         @ Timer 4 Signal B 
                                   
PIOTCLK5   =     6         @ Timer 5 Clock signal 
PIOTIOA5   =     7         @ Timer 5 Signal A 
PIOTIOB5   =     8         @ Timer 5 Signal B 
                                    
PIOIRQ0    =     9         @ External Interrupt 0 
PIOIRQ1    =     10        @ External Interrupt 1 
PIOIRQ2    =     11        @ External Interrupt 2 
PIOIRQ3    =     12        @ External Interrupt 3 
PIOFIQ     =     13        @ Fast Interrupt 
                                   
PIOSCK0    =     14        @ USART 0 signal 
PIOTXD0    =     15        @ USART 0 transmit data 
PIORXD0    =     16        @ USART 0 receive data  
                                  
PIOSCK1    =     17        @ USART 1 clock signal  
PIOTXD1    =     18        @ USART 1 transmit data 
PIORXD1    =     19        @ USART 1 receive data  
                                   
PIOSCK2    =     20        @ USART 2 clock signal   
PIOTXD2    =     21        @ USART 2 transmit data  
PIORXD2    =     22        @ USART 2 receive data   
                                   
PIOSPCK    =     23        @ SPI clock signal  
PIOMISO    =     24        @ SPI Master In Slave 
PIOMOSI    =     25        @ SPI Master Out Slave 
PIONPCS0   =     26        @ SPI Peripheral Chip Select 0 
PIONSS     =     PIONPCS0    
PIONPCS1   =     27        @ SPI Peripheral Chip Select 1 
PIONPCS2   =     28        @ SPI Peripheral Chip Select 2 
PIONPCS3   =     29        @ SPI Peripheral Chip Select 3 

@ PIO Controller B 
PIOTCLK0    =    19        @ Timer 0 Clock signal input 
PIOTIOA0    =    20        @ Timer 0 Signal A   
PIOTIOB0    =    21        @ Timer 0 Signal B   
                                   
PIOTCLK1    =    22        @ Timer 1 Clock signal 
PIOTIOA1    =    23        @ Timer 1 Signal A 
PIOTIOB1    =    24        @ Timer 1 Signal B 
                                       
PIOTCLK2    =    25        @ Timer 2 Clock signal 
PIOTIOA2    =    26        @ Timer 2 Signal A 
PIOTIOB2    =    27        @ Timer 2 Signal B 
                                     
PIOMCKO     =    17        @ Master Clock Output 
                                  
PIOBMS      =    18        @ Boot Mode Select 
                                  
PIOMPI_NOE  =    0         @ MPI output enable 
PIOMPI_NLB  =    1         @ MPI lower byte select 
PIOMPI_NUB  =    2         @ MPI upper byte select 

LED1        =    (1<<8)         @ LED 1 (linke LED) 
LED2        =    (1<<9)         @ LED 2 
LED3        =   (1<<10)         @ LED 3 
LED4        =   (1<<11)         @ LED 4 
LED5        =   (1<<12)         @ LED 5 
LED6        =   (1<<13)         @ LED 6 
LED7        =   (1<<14)         @ LED 7 
LED8        =   (1<<15)         @ LED 8 
ALL_LEDS    =   (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8)

KEY1        =    (1<<3)         @ TASTE 1 (linke Taste) auf PB3 
KEY2        =    (1<<4)         @ TASTE 2 auf PB4 
KEY3        =    (1<<5)         @ TASTE 3 auf PB5 
KEY4        =    (1<<9)         @ TASTE 4 auf PA9/IRQ0 
ALL_KEYS    =    (KEY1|KEY2|KEY3)                                            
#endif 
