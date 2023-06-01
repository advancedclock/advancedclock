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
       //
    }
}
