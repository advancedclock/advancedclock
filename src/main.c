#include <MKL25Z4.h>
#include <stdbool.h>
#include "led.h"
#include "delay.h"

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
