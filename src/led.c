#include <MKL25Z4.h>
#include "led.h"

//PTB18 = RED LED
//PTB19 = GREEN LED
//PTD1  = BLUE LED	

// Function to set the status of the red LED
void setRedLED(const bool status)
{
	if (status)
	{
		PTB->PCOR |= (1 << 18);  // Set red LED
	}
	else
	{
		PTB->PSOR |= (1 << 18);  // Clear red LED
	}
}

// Function to set the status of the green LED
void setGreenLED(const bool status)
{
	if (status)
	{
		PTB->PCOR |= (1 << 19);  // Set green LED
	}
	else
	{
		PTB->PSOR |= (1 << 19);  // Clear green LED
	}
}

// Function to set the status of the blue LED
void setBlueLED(const bool status)
{
	if (status)
	{
		PTD->PCOR |= (1 << 1);  // Set the blue LED
	}
	else
	{
		PTD->PSOR |= (1 << 1);  // Clear the blue LED
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
	setRedLED(false);
	setGreenLED(false);
  setBlueLED(false);
}
