#include "Distance.h"

void irInit()
{

	// Enable clock to ADC0
    SIM->SCGC6 |= SIM_SCGC6_ADC0(1);
    
    // Enable clock to PORTs
    SIM->SCGC5 |= SIM_SCGC5_PORTA(1) | SIM_SCGC5_PORTB(1);
    
    // The IR LED is connected to PTA16. Configure the pin as a GPIO output pin.
    PORTA->PCR[16] &= ~0x7FF;
    PORTA->PCR[16] |= PORT_PCR_MUX(1);
    PTA->PDDR |= (1<<16);
    
    // IR LED off
    PTA->PSOR = (1<<16);
    
    // The ouptut of the transistor is connectd to PTB0. Configure the pin as
    // ADC input pin (channel 8).
    PORTB->PCR[0] &= ~0x7FF;
    
    // Configure ADC
    // - ADLPC = 1 : Low-power configuration. The power is reduced at the 
    //               expense of maximum clock speed.
    // - ADIV[1:0] = 00 : The divide ratio is 1 and the clock rate is input 
    //                    clock.
    // - ADLSMP = 1 : Long sample time.
    // - MODE[1:0] = 11 : Single-ended 16-bit conversion
    // - ADICLK[1:0] = 01 : (Bus clock)/2
    ADC0->CFG1 = 0x9D;
	
}
uint16_t ir_sample(void)
{
    // Start a conversion on channel 8
    ADC0->SC1[0] = 8;
    
    // Wait for conversion to complete
    while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
    {}
        
    // Read the result
    uint16_t res = (uint16_t)ADC0->R[0];
        
    // Complement the result, because the voltage falls with increasing IR level
    // and we want the result to rise with increasing IR level.
    return (0xFFFF - res);
}

int irReadDistance(const uint8_t n)
{
		
	
	  int32_t cumulative_difference = 0;
    
    for(int i=0; i<n; i++)
    {        
        //IR LED on 
			PTA->PCOR=(1<<16);
			delay_us(2000);
			uint16_t on_brightness =ir_sample();
			
			//IR LED off
			PTA->PSOR =(1<<16);
			delay_us(2000);
			uint16_t off_brightness =ir_sample();
			
			cumulative_difference += on_brightness - off_brightness;
		
    }

    uint16_t distance  = (uint16_t) (cumulative_difference / n);
		
		if(distance >3000)
		{
			distance = 2; 
		}
		else if(distance >1000)
		{
			distance =1;
		}
		else
		{
			distance=0;
		}
		
		
		

		return distance;
}
