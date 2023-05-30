#ifndef LED_H
#define LED_H

#include <MKL25Z4.h>
#include <stdbool.h>

void setLEDStatus(const bool r, const bool g, const bool b);
void rgb_init(void);

#endif
