/*! ***************************************************************************
 *
 * \brief     Blinky
 * \file      main.c
 * \author    Hugo Arends  
 * \date      June 2021
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
#include <MKL25Z4.h>
#include <stdbool.h>

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

    while(1)
    {
        rgb_onoff(true, false, false);
        delay_us(1000000UL);
        rgb_onoff(false, true, false);
        delay_us(1000000UL);
        rgb_onoff(false, false, true);
        delay_us(1000000UL);
        rgb_onoff(false, false, false);
        delay_us(1000000UL);
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
