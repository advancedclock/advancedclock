/*! ***************************************************************************
 *
 * \brief     Advanced clock
 * \file      main.c
 * \author    Anthony_Jaap-Jan_Jeroen_Koen
 * \date      May 2023
 *
 * \copyright 
 *Anthony
 *Jaap-Jan
 *Jeroen
 *Koen
 *
 *             
 *            
 *            
 *            
 *
 *****************************************************************************/
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdio.h>

#include "uart0.h"

// Local function prototypes
static void delay_us(uint32_t d);
void rgb_init(void);
void rgb_onoff(const bool r, const bool g, const bool b);

/*!
 * \brief Main application
 */
int main(void)
{
   rgb_init();
	 //UART START
	 uart0_init();    
   uart0_send_string("Starting Advanced clock\r\n");

    while(1)
    {
			uart0_send_string("Advanced clock alive\r\n");
      delay_us(1000000);
			
			 // Check for incoming characters
        if(uart0_num_rx_chars_available() > 0)
        {
            // Get the character
            char c = uart0_get_char();
            
            // Turn on/off the RGB LED accordingly
            switch(c)
            {
            case 'r':
            case 'R':
            {
                rgb_onoff(true, false, false);
            }
            break;
            case 'g':
            case 'G':
            {
                rgb_onoff(false, true, false);
            }
            break;
            case 'b':
            case 'B':
            {
                rgb_onoff(false, false, true);
            }
            break;
            case ' ':
            {
                rgb_onoff(false, false, false);
            }
            break;
            default:
            {
                uart0_send_string("character: ");
                uart0_put_char(c);
                uart0_send_string("\r\n");
            }
            break;
            }
        }
    }
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
 * \brief Initialises the onboard RGB LED
 *
 * This functions initializes the onboard RGB LED. The LEDs are connected as
 * follows:
 * - Red: PTB18
 * - Green: PTB19
 * - Blue: PTD1
 */
void rgb_init(void)
{
    // Enable clock to PORTS
    SIM->SCGC5 |= SIM_SCGC5_PORTB(1) | SIM_SCGC5_PORTD(1);

    // Enable clock to TPMs
    SIM->SCGC6 |= SIM_SCGC6_TPM0(1) | SIM_SCGC6_TPM2(1);

    // Set clock source: MCGFLLCLK clock or MCGPLLCLK/2
    //
    // Notice that the actual TPM clock frequency is determined by the setting
    // in the file system_MKL25Z4.h. If CLOCK_SETUP == 1, which is the default
    // in the given projects, then the PLLFLLSEL bit in SIM->SOPT2 is set and
    // the MCGPLLCLK/2 is selected. All the TPMs then run at 48 MHz.
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    // Select alternative functions on the pins connected to the RGB LEDs
    // PTB18 (red)  : TPM2_CH0
    // PTB19 (green): TPM2_CH1
    // PTD1  (blue) : TPM0_CH1
    PORTB->PCR[18] = PORT_PCR_MUX(3);
    PORTB->PCR[19] = PORT_PCR_MUX(3);
    PORTD->PCR[1]  = PORT_PCR_MUX(4);

    // Set initial values: all LEDs off
    rgb_onoff(false, false, false);

    // Set modulo value. We use the full 16-bit range, which allows us to
    // control each RGB LED in 2^16 = 65536 steps.
    //
    // Assuming the TPM is counting at 48 MHz, the PWM frequency is equal to
    // 48 MHz / 65536 = 732.4 Hz.
    TPM2->MOD = 0xFFFF;
    TPM0->MOD = 0xFFFF;

    // Set all channels to edge-aligned low-true PWM. We use low-true PWM,
    // because the cathodes of the LEDs are connected to the pins. This means
    // That an LED is on with a low value.
    TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1);
    TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1);
    TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1);

    // Start TPMs. Prescaler are kept at the default values: 1.
    TPM2->SC = TPM_SC_CMOD(1);
    TPM0->SC = TPM_SC_CMOD(1);
}

inline void rgb_onoff(const bool r, const bool g, const bool b)
{
    // Set convenient on/off values for each color here, ranging from
    // 0 to 65535. A lower value means that the LED will be lit more dim.
    //
    // DO NOT SET THIS NUMBER HIGHER THAN 4096, BECAUSE THE LEDS ARE VERY
    // BRIGHT!
    //
    const uint16_t red = 2048;
    const uint16_t green = 2048;
    const uint16_t blue = 2048;

    // Set the channel compare values
    TPM2->CONTROLS[0].CnV = r ? red : 0;
    TPM2->CONTROLS[1].CnV = g ? green : 0;
    TPM0->CONTROLS[1].CnV = b ? blue : 0;
}
