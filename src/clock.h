#ifndef CLOCK_H
#define CLOCK_H

#include <MKL25Z4.h>
#include <stdbool.h>

extern volatile bool updateFlag;

// prototype here
void PITInit();

#endif
