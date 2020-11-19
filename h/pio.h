//----------------------------------------------------------------------------
// File Name           : pio.h
// Object              : Parallel I/O Header File
//
//* 1.0 27/10/02 GR     : Creation
//----------------------------------------------------------------------------

#ifndef pio_h
#define pio_h

#include    "std_c.h"

/*------------------------------------------------------------*/
/* User Interface Parallel I/O Interface Structure Definition */
/*------------------------------------------------------------*/

typedef struct
{
  at91_reg        PIO_PER ;           /* PIO Enable Register */
  at91_reg        PIO_PDR ;           /* PIO Disable Register */
  at91_reg        PIO_PSR ;           /* PIO Status Register */
  at91_reg        Reserved0 ;
  at91_reg        PIO_OER ;           /* Output Enable Register */
  at91_reg        PIO_ODR ;           /* Output Disable Register */
  at91_reg        PIO_OSR ;           /* Output Status Register */
  at91_reg        Reserved1 ;
  at91_reg        PIO_IFER ;          /* Input Filter Enable Register */
  at91_reg        PIO_IFDR ;          /* Input Filter Disable Register */
  at91_reg        PIO_IFSR ;          /* Input Filter Status Register */
  at91_reg        Reserved2 ;
  at91_reg        PIO_SODR ;          /* Set Output Data Register */
  at91_reg        PIO_CODR ;          /* Clear Output Data Register */
  at91_reg        PIO_ODSR ;          /* Output Data Status Register */
  at91_reg        PIO_PDSR ;          /* Pin Data Status Register */
  at91_reg        PIO_IER ;           /* Interrupt Enable Register */
  at91_reg        PIO_IDR ;           /* Interrupt Disable Register */
  at91_reg        PIO_IMR ;           /* Interrupt Mask Register */
  at91_reg        PIO_ISR ;           /* Interrupt Status Register */
  at91_reg        PIO_MDER ;          /* Multi Driver Enable Register */
  at91_reg        PIO_MDDR ;          /* Multi Driver Disable Register */
  at91_reg        PIO_MDSR ;          /* Multi Driver Status Register */
} StructPIO ;

#define PIOB_BASE       ((StructPIO *) 0xFFFF0000)      /* Parallel I/O Controller B */
#define PIOA_BASE       ((StructPIO *) 0xFFFEC000)      /* Parallel I/O Controller A */

/* PIO Controller A */
#define PIOTCLK3        0         /* Timer 3 Clock signal */
#define PIOTIOA3        1         /* Timer 3 Signal A */
#define PIOTIOB3        2         /* Timer 3 Signal B */
                                   
#define PIOTCLK4        3         /* Timer 4 Clock signal */
#define PIOTIOA4        4         /* Timer 4 Signal A */
#define PIOTIOB4        5         /* Timer 4 Signal B */
                                   
#define PIOTCLK5        6         /* Timer 5 Clock signal */
#define PIOTIOA5        7         /* Timer 5 Signal A */
#define PIOTIOB5        8         /* Timer 5 Signal B */
                                    
#define PIOIRQ0         9         /* External Interrupt 0 */
#define PIOIRQ1         10        /* External Interrupt 1 */
#define PIOIRQ2         11        /* External Interrupt 2 */
#define PIOIRQ3         12        /* External Interrupt 3 */
#define PIOFIQ          13        /* Fast Interrupt */
                                   
#define PIOSCK0         14        /* USART 0 signal */
#define PIOTXD0         15        /* USART 0 transmit data */
#define PIORXD0         16        /* USART 0 receive data  */
                                  
#define PIOSCK1         17        /* USART 1 clock signal  */
#define PIOTXD1         18        /* USART 1 transmit data */
#define PIORXD1         19        /* USART 1 receive data  */
                                   
#define PIOSCK2         20        /* USART 2 clock signal   */
#define PIOTXD2         21        /* USART 2 transmit data  */
#define PIORXD2         22        /* USART 2 receive data   */
                                   
#define PIOSPCK         23        /* SPI clock signal */ 
#define PIOMISO         24        /* SPI Master In Slave */
#define PIOMOSI         25        /* SPI Master Out Slave */
#define PIONPCS0        26        /* SPI Peripheral Chip Select 0 */
#define PIONSS          PIONPCS0    
#define PIONPCS1        27        /* SPI Peripheral Chip Select 1 */
#define PIONPCS2        28        /* SPI Peripheral Chip Select 2 */
#define PIONPCS3        29        /* SPI Peripheral Chip Select 3 */

/* PIO Controller B */
#define PIOTCLK0        19        /* Timer 0 Clock signal input */
#define PIOTIOA0        20        /* Timer 0 Signal A   */
#define PIOTIOB0        21        /* Timer 0 Signal B   */
                                   
#define PIOTCLK1        22        /* Timer 1 Clock signal */
#define PIOTIOA1        23        /* Timer 1 Signal A */
#define PIOTIOB1        24        /* Timer 1 Signal B */
                                       
#define PIOTCLK2        25        /* Timer 2 Clock signal */
#define PIOTIOA2        26        /* Timer 2 Signal A */
#define PIOTIOB2        27        /* Timer 2 Signal B */
                                     
#define PIOMCKO         17        /* Master Clock Output */
                                  
#define PIOBMS          18        /* Boot Mode Select */
                                  
#define PIOMPI_NOE      0         /* MPI output enable */
#define PIOMPI_NLB      1         /* MPI lower byte select */
#define PIOMPI_NUB      2         /* MPI upper byte select */

#define LED1            (1<<8)         /* LED 1 (linke LED) */
#define LED2            (1<<9)         /* LED 2 */
#define LED3           (1<<10)         /* LED 3 */
#define LED4           (1<<11)         /* LED 4 */
#define LED5           (1<<12)         /* LED 5 */
#define LED6           (1<<13)         /* LED 6 */
#define LED7           (1<<14)         /* LED 7 */
#define LED8           (1<<15)         /* LED 8 */
#define ALL_LEDS       (LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8)

#define KEY1            (1<<3)         /* TASTE 1 (linke Taste) auf PB3 */
#define KEY2            (1<<4)         /* TASTE 2 auf PB4 */
#define KEY3            (1<<5)         /* TASTE 3 auf PB5 */
#define KEY4            (1<<9)         /* TASTE 4 auf PA9/IRQ0 */
#define ALL_KEYS        (KEY1|KEY2|KEY3)                                            
#endif /* pio_h */
