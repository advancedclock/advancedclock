#ifndef CLOCK_H
#define CLOCK_H

#include <MKL25Z4.h>
#include <stdbool.h>
#include "datetime.h"

extern volatile uint32_t unixTimeSeconds;
extern volatile datetime_t unixTime;
extern volatile bool timeSyncFlag;
extern volatile char dateString[11];
extern volatile char timeString[9];


// prototype here
void PITInit(void);
void timeSyncCheck(volatile uint32_t * unixTimeSeconds);
void getTimeAsString(uint32_t unixTimeSeconds, volatile char *timeString);
void getDateAsString(uint32_t unixTimeSeconds, volatile char *dateString);

void setUnixTime(uint32_t val);


#endif
