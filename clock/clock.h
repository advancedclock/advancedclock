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
bool ClockOutOfSynq(volatile uint32_t currentUnixTimeSeconds);
void GetTimeAsString(volatile char *timeString);
void GetDateAsString(volatile char *dateString);
void GetDateTime(datetime_t * datetime);

void SetUnixTimeClock(uint32_t val);

uint32_t GetUnixTimeClock();


#endif
