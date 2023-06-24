/*! ***************************************************************************
 *
 * \brief     Low level driver for the infrared proximity sensor
 * \file      ir.h
 * \author    Hugo Arends
 * \date      July 2021
 *
 * \copyright 2021 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#include "irDistanceSensor.h"
#include <math.h>

/*!
 * \brief Initialises the IR proximity sensor
 *
 * This functions initializes the pins for the IR led and IR transistor
 * - PTA16 is configured as an output pin
 * - PTB0 is configured as an analog input (ADC channel 8)
 */
void ir_init(void)
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
    PORTB->PCR[0] &= ~0x7FF; // 011111111111
    
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

/*!
 * \brief Creates a blocking delay
 *
 * Software delay of approximately 1.02 us, depending on compiler version,
 * CPU clock frequency and optimizations.
 * - C compiler: ARMClang v6
 * - Language C: gnu11
 * - CPU clock: 48 MHz
 * - Optimization level: -O3
 * - Link-Time Optimization: disabled
 *
 * \param[in]  d  delay in microseconds
 */                              
static void delay_us(uint32_t d)
{

#if (CLOCK_SETUP != 1)
#warning This delay function does not work as designed
#endif

    volatile uint32_t t;

    for(t=4*d; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
}

/*!
 * \brief Samples the IR proximity sensor
 *
 * Take one samples from the IR proximity sensor.
 *
 * \return  The complemented 16-bit ADC value
 */
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

/*!
 * \brief Measures the IR proximity sensor
 *
 * Measures the IR proximity sensor and averages the result.
 *
 * \param[in]  n  Number of samples for taking the average
 *
 * \return  Range to an object
 *
 * \todo Change the conversion result so it returns either of the following
 *       values:
 *        - 0: there is no object within 10 cm
 *        - 1: there is an object within 5 .. 10 cm
 *        - 2: there is an object within 0 .. 5 cm
 */
uint16_t ir_measure(const uint8_t n)
{
    int32_t cumulative_difference = 0;
    
    for(int i=0; i<n; i++)
    {        
        // IR LED on
        PTA->PCOR = (1<<16);
        delay_us(2000);
        uint16_t on_brightness = ir_sample();        

        // IR LED off
        PTA->PSOR = (1<<16);
        delay_us(2000);
        uint16_t off_brightness = ir_sample();
        
        cumulative_difference += on_brightness - off_brightness;
    }

    uint16_t result = (uint16_t)(cumulative_difference / n);
        
    return sizeof(uint16_t) - result;
}

// Function for converting raw sensor value to human readable integer
int getDistanceCm()
{
	// Typical plot line for a TCRT5000 is:
	// y = 2000+59000 / ( 1 + 1000e^-x)
	// This function uses the inverse of y.
	
		// Get raw distance value from sensor
		double value = (int)ir_measure(10);
		double result = 0;
		
		// Check if value from distance sensor is sane.
		// For TCRT5000 its between 2000 & 70000 (1 to 15 cm).
    if (value > 2000 && value < 70000)
    {
        // result for function y = -ln((61000 - x)/(1000(-2000+x)))
        result = -log((61000 - value) / (1000 * (-2000 + value)));
        int result_int = (int)(result + 0.5); // add 0.5 to round up
        return result_int;
    }
    else
    {
        return -1;
    }
}
