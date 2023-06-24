#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MKL25Z4.h>
#include "Delay.h"


#define MASK(x) (1UL << (x))


#define _XTAL_FREQ  8000000

// Available Functions:
void temp_init(void);
float get_temp_C(void); // Returns the temperature in celsius 
unsigned int OneWireReset(void); // Sends a reset pulse to the sensor 
void OneWireWriteBit(unsigned char); // write a single bit to the OneWire
unsigned char OneWireReadBit(void); // reads a single bit 
void OneWireWriteByte(unsigned char); // writes a byte 
unsigned char OneWireReadByte(void); // reads a byte 
unsigned char OneWireRead(void); // reads the current status of the bus
void OneWireHigh(void); // sets the bus high
void OneWireRelease(void); // releases the bus 

#endif // TEMPERATURE_H
