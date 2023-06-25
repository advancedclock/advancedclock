#ifndef LED_H
#define LED_H

#include <MKL25Z4.h>
#include <stdbool.h>

void setRedLED(const bool status);
void setGreenLED(const bool status);
void setBlueLED(const bool status);

void rgb_init(void);

#endif
