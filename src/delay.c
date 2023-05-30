#include <MKL25Z4.h>
#include "delay.h"

// Troubleshooting
#include <stdbool.h>
#include <stdio.h>

void delay_us(uint32_t d)
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
