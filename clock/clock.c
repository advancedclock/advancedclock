#include <MKL25Z4.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clock.h"
#include "led.h"
#include "datetime.h"

#define RECENTUNIXTIME 1685449404		// Unix tijd voor 2023-05-30 12:23:24 (UTC)

volatile uint32_t unixTimeSeconds = 0;
volatile datetime_t unixTime = {0, 0, 0, 0, 0, 0};
volatile bool timeSyncFlag = false;
volatile char dateString[11];
volatile char timeString[9];

// Function for initializing the PIT Timer
void PITInit(void)
{
	// Enable clock for PIT module
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

	// Enable PIT timer module and freeze the timer when debugging
	PIT->MCR = PIT_MCR_FRZ_MASK;

	// Set the PIT interrupt frequency
	// CPU / 
	PIT->CHANNEL[0].LDVAL = 2399999;

	// Enable interrupts for the PIT channel 0
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

	// Clear any pending interrupt
	NVIC_ClearPendingIRQ(PIT_IRQn);

	// Set the priority for the PIT interrupt
	NVIC_SetPriority(PIT_IRQn, 3);

	// Enable the PIT interrupt
	NVIC_EnableIRQ(PIT_IRQn);

	// Start the timer
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}


// PIT interrupt handler
void PIT_IRQHandler(void)
{
	// Clear the interrupt flag
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

	static uint32_t count = 0;
	count++;

	// Toggle the LED every 1 second
	if (count == 1)
	{
		setLEDStatus(false, false, false);
	}

	if (count == 10)
	{
		setLEDStatus(true, true, false);
		count = 0;
		unixTimeSeconds++;
	}
}

// Check if time is in sync by comparing current time with a known recent timestamp
void TimeSyncCheck(volatile uint32_t * unixTimeSeconds)
{
		if (*unixTimeSeconds < RECENTUNIXTIME)
		{
				timeSyncFlag = false;
		}
		
		if (*unixTimeSeconds > RECENTUNIXTIME)
		{
				timeSyncFlag = true;
		}
}

// Function for converting UnixTimeSeconds to a string HH:MM:SS
void GetTimeAsString(volatile char *timeString)
{
		// Init variables
		char hourString[3];
		char minuteString[3];
		char secondString[3];
	
		// Send UnixTimeSeconds to datetime.c
		RTC_HAL_ConvertSecsToDatetime(&unixTimeSeconds, &unixTime);
	
		// Put time in local variables
		uint32_t hour = unixTime.hour;
		uint32_t minute = unixTime.minute;
		uint32_t second = unixTime.second;
		
		// Put variables in string using sprintf
		sprintf(hourString, "%02d", hour);
		sprintf(minuteString, "%02d", minute);
		sprintf(secondString, "%02d", second);
		
		// Clear string
		strcpy(timeString, "");
		
		// Merge strings
		strcat(timeString, hourString);
		strcat(timeString, ":");
		strcat(timeString, minuteString);
		strcat(timeString, ":");
		strcat(timeString, secondString);
}

// Function for converting UnixTimeSeconds to a string DD-MM-YYYY
void GetDateAsString(volatile char *dateString)
{
		// Init variables
		char dayString[3];
		char monthString[3];
		char yearString[5];
	
		// Send UnixTimeSeconds to datetime.c
		RTC_HAL_ConvertSecsToDatetime(&unixTimeSeconds, &unixTime);
	
		// Put time in local variables
		uint32_t day = unixTime.day;
		uint32_t month = unixTime.month;
		uint32_t year = unixTime.year;
		
		// Put variables in string using sprintf
		sprintf(dayString, "%02d", day);
		sprintf(monthString, "%02d", month);
		sprintf(yearString, "%04d", year);
		
		// Clean old date from string
		strcpy(dateString, "");
		
		// Merge strings
		strcat(dateString, dayString);
		strcat(dateString, "-");
		strcat(dateString, monthString);
		strcat(dateString, "-");
		strcat(dateString, yearString);
}

void SetUnixTimeClock(uint32_t val)
{
	unixTimeSeconds = val;
	RTC_HAL_ConvertSecsToDatetime(&unixTimeSeconds, &unixTime);
}

void GetDateTime(datetime_t * datetime)
{
	datetime->year = unixTime.year;
	datetime->month = unixTime.month;
	datetime->day = unixTime.day;
	datetime->hour = unixTime.hour;
	datetime->minute = unixTime.minute;
	datetime->second = unixTime.second;
}


