#ifndef DISTANCE_H
#define DISTANCE_H

#include <MKL25Z4.h>
#include "delay.h"
//available functions
void irInit() ;
int irReadDistance(const uint8_t n);

#endif DISTANCE_H
