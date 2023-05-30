#include <MKL25Z4.h>
#include <stdbool.h>
#include "led.h"
#include "delay.h"
#include "clock.h"

int main(void)
{
    rgb_init();
	
		// Give PITInit a frequency in Hz for IRQ
		PITInit(10);

    while(1)
    {
				// RED
        //setLEDStatus(true, false, false);
				
				// GREEN
        //setLEDStatus(false, true, false);
				
				// BLUE
        //setLEDStatus(false, false, true);
			
			
//				// Loop through colors
//				setLEDStatus(true, false, false);
//        delay_us(1000000UL);
//        setLEDStatus(false, true, false);
//        delay_us(1000000UL);
//        setLEDStatus(false, false, true);
//        delay_us(1000000UL);
//        setLEDStatus(false, false, false);
//        delay_us(1000000UL);
			
			
		// Enable clock for Port B
    //SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    }
}
