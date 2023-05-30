#include <MKL25Z4.h>
#include <stdbool.h>
#include "../led.h"

// Local function prototypes
static void delay_us(uint32_t d);

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
