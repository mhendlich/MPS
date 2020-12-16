// Loesung zu Termin3
// Aufgabe 1
// von:
// vom: 
// 

#include <stdint.h>

#include "../h/pmc.h"
#include "../h/tc.h"
#include "../h/pio.h"
#include "../h/aic.h"

inline uint8_t IsKeydown(const IO_Switches keyNr)
{
	StructPIO* piobaseB = PIOB_BASE;	
	
	static const uint8_t keys[] = {KEY1, KEY2, KEY3};

	if (keyNr > IO_SW3)
		return 0;

	const uint8_t key = keys[keyNr];

	// Ist die gewünschte Tasten schon unter der Kontrolle der PIO?
	if (~piobaseB->PIO_PSR & key)
	{
		piobaseB->PIO_PER = key;

		// Ist die gewünschte Taste als input konfiguriert?
		if (piobaseB->PIO_OSR & key)
			piobaseB->PIO_ODR = key;
	}

	// Aufgabe: Hier wurde das falsche PIO-Register genutzt! 
	// Berichtigen Sie diesen Fehler, damit der Pin-Status ausgelesen wird.
	// Beachten Sie zudem, ob die Tasten high- oder low-active sind!
	if ( ( ~piobaseB->PIO_PDSR & key ) ) //wenn low-active pdsr invertieren
		return 1;

	return 0;
}

void taste_irq_handler (void) __attribute__ ((interrupt));
void Timer3_init (void);


// Interruptserviceroutine für die Tasten SW1 und SW2
void taste_irq_handler (void)
{
  	StructPIO* piobaseB = PIOB_BASE;		// Basisadresse PIO B
  	StructAIC* aicbase  = AIC_BASE;			// Basisadresse des Advanced Interrupt Controller
	StructTC* timerbase3 = TCB3_BASE;
	StructPMC* pmcbase = PMC_BASE;
	
	if(IsKeydown(IO_SW1)){
		piobaseB->PIO_PER = (1<<PIOTIOA3);
		PMC_BASE->PMC_PCDR = 0x200;
	}
	else if (IsKeydown(IO_SW2)){
		PMC_BASE->PMC_PCER = 0x200;
		piobaseB->PIO_PDR = (1<<PIOTIOA3);

	}
	
	aicbase->AIC_EOICR = piobaseB->PIO_ISR;	//__
}

// Timer3 initialisieren
// Ein symetrisches Rechtecksignal zur Ansteueren einer Kolbenhubpumpe 
// an TIOA3 wird erzeugt
// Der gegebene Programmrahmen stellt noch nicht die richtige Frequenz ein
void Timer3_init( void )
{
  StructTC* timerbase3  = TCB3_BASE;	// Basisadressse TC Block 1
  StructPIO* piobaseA   = PIOA_BASE;	// Basisadresse PIOB

  timerbase3->TC_CCR = TC_CLKDIS;	// Disable Clock
 
  // Initialisieren Timer 3
  timerbase3->TC_CMR =
    TC_ACPC_CLEAR_OUTPUT  |    //ACPC    : Register C clear TIOA
    TC_ACPA_SET_OUTPUT    |    //ACPA    : Register A set TIOA
    TC_WAVE               |    //WAVE    : Waveform mode
    TC_CPCTRG             |    //CPCTRG  : Register C compare trigger enable
    TC_CLKS_MCK8;           //TCCLKS  : MCKI / 8

  // Initialize the counter:
  timerbase3->TC_RA = 31250;	//Contains the value at which TIOA gets set
  timerbase3->TC_RC = 62500;	//Contains the value at which TIOA gets cleared
  
  //(25MHz/8)/RC = 50Hz
  //(25MHz/8)/50Hz = RC
  // RC = 62500
  // RA = RC/2

  // Start the timer :
  timerbase3->TC_CCR = TC_CLKEN ;	//Enables the clock
  timerbase3->TC_CCR = TC_SWTRG ;	//Sets counter to 0 and starts the clock
  // Initialisieren vom Ausgang TIOA3 und setzen auf Low-Signal
  piobaseA->PIO_PER  = (1<<PIOTIOA3) ;	//Enables PIO control on the corresponding pin
  piobaseA->PIO_OER  = (1<<PIOTIOA3) ;	//Enables output on the corresponding pin
  piobaseA->PIO_CODR = (1<<PIOTIOA3) ;	//Clears PIO output on the corresponding
}

void InterruptInit(void)
{
	StructAIC* aicbase = AIC_BASE;
	StructPIO* piobaseB = PIOB_BASE;

	// Aufgabe: Setzen Sie die richtigen Register ein, indem Sie die Kommentare
	// in den jeweiligen Zeilen als Hinweise nehmen!

	aicbase->AIC_IDCR = (1 << PIOB_ID);	// Disable all interrupt handling for PIOB
	aicbase->AIC_ICCR = (1 << PIOB_ID);	// Clear all pending interrupts from PIOB

	aicbase->AIC_SVR[PIOB_ID] = (unsigned int) taste_irq_handler;	// Set the irq-handler for interrupts raised by PIOB
	aicbase->AIC_SMR[PIOB_ID] = AIC_PRIOR;				// Set the highest priority for interrupts from PIOB

	aicbase->AIC_IECR = (1 << PIOB_ID);

	piobaseB->PIO_IER = KEY1 | KEY2;	// Enables interrupts in PIOB for the first two switches
}

int main(void)
{

	StructPMC* pmcbase	= PMC_BASE;		// Basisadresse des PMC
	StructPIO* piobaseA   	= PIOA_BASE;		// Basisadresse PIO A
	StructPIO* piobaseB   	= PIOB_BASE;		// Basisadresse PIO B

	pmcbase->PMC_PCER	= 0x4200;	// Peripheral Clocks einschalten für PIOB, TC3 
	
// ab hier entsprechend der Aufgabestellungen ergaenzen
//**************************************************

	InterruptInit();
	Timer3_init();
	
	while(1)
	{

	}
	
	return 0;
}
