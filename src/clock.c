// Handige blogpost
// https://medium.com/swlh/arm-kl25-periodic-interrupt-timer-8d4b184f0088

#include <MKL25Z4.h>
#include <stdbool.h>
#include "clock.h"
#include "led.h"

#include "delay.h"		// only used for debugging. Delete from IRQhandler later


#define RECENTUNIXTIME 1685449404		// Unix tijd voor 2023-05-30 12:23:24 (UTC)

void PITInit()
{
    // Enable clock for PIT module
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // Enable PIT timer module and freeze the timer when debugging
    PIT->MCR = PIT_MCR_FRZ_MASK;

    // Set the desired timer period
	  PIT->CHANNEL[0].LDVAL = (SystemCoreClock - 1);

    // Enable interrupts for the PIT channel 0
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

    // Clear any pending interrupt
    NVIC_ClearPendingIRQ(PIT_IRQn);

    // Set the priority for the PIT interrupt
    NVIC_SetPriority(PIT_IRQn, 3);

    // Enable the PIT interrupt
    NVIC_EnableIRQ(PIT_IRQn);

    // Start the timer
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void PIT_IRQHandler(void) {
    // Clear the interrupt flag
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

    static uint32_t count = 0;
    count++;

    // Toggle the LED every 1 second
    if (count == 1)
		{
				// Blue light
				setLEDStatus(false, false, true);
			
				// Blocking delay of 1 second
				delay_us(1000000UL);
			
				// Green light
				setLEDStatus(false, true, false);
			
				// Reset counter
				count = 0;
    }
}
