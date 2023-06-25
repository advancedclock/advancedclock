#include <MKL25Z4.h>
#include "led.h"

//PTB18 = RED LED
//PTB19 = GREEN LED
//PTD1  = BLUE LED	

inline void setLEDStatus(const bool r, const bool g, const bool b)
{
	// Set the red led
	if (r)
	{
		PTB->PCOR |= (1 << 18);
	}
	else
	{
		PTB->PSOR |= (1 << 18);
	}
	
	// Set the green led
	if (g)
	{
		PTB->PCOR |= (1 << 19);
	}
	else
	{
		PTB->PSOR |= (1 << 19);
	}
	
	// Set the blue led
	if (b)
	{
		PTD->PCOR |= (1 << 1);
	}
	else
	{
		PTD->PSOR |= (1 << 1);
	}
}

void rgb_init(void)
{
	// Enable clock to GPIO port B & D
	SIM->SCGC5 |= (1UL <<  10);
	SIM->SCGC5 |= (1UL <<  12);
	
	// Configure PTB18 as GPIO
	PORTB->PCR[18] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[18] |= PORT_PCR_MUX(1);
	// Configure PTB19 as GPIO
	PORTB->PCR[19] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[19] |= PORT_PCR_MUX(1);
	// Configure PTD1 as GPIO
	PORTD->PCR[1] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[1] |= PORT_PCR_MUX(1);
	
	// SET LED pins to output
	PTB->PDDR |= (1 << 18);
	PTB->PDDR |= (1 << 19);
	PTD->PDDR |= (1 << 1);
	
  // Set initial values: all LEDs off
  setLEDStatus(false, false, false);
}
