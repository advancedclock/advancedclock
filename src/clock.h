#ifndef CLOCK_H
#define CLOCK_H

#include <MKL25Z4.h>
#include <stdbool.h>
#include "datetime.h"

extern volatile uint32_t unixTimeSeconds;
extern volatile datetime_t unixTime;
extern volatile bool timeSyncFlag;

// prototype here
void PITInit(uint32_t PITfrequency);
void timeSyncCheck(uint32_t * unixTimeSeconds);
void getTimeAsString(uint32_t unixTimeSeconds, char *timeString);
void getDateAsString(uint32_t unixTimeSeconds, char *dateString);

#endif
