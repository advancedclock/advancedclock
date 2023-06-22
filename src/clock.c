// Handige blogpost
// https://medium.com/swlh/arm-kl25-periodic-interrupt-timer-8d4b184f0088

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

void PITInit(uint32_t PITfrequency)
{
    // Enable clock for PIT module
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // Enable PIT timer module and freeze the timer when debugging
    PIT->MCR = PIT_MCR_FRZ_MASK;

    // Set the desired timer period
	  PIT->CHANNEL[0].LDVAL = ((SystemCoreClock / PITfrequency) - 1);

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

void PIT_IRQHandler(void) {
    // Clear the interrupt flag
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

    static uint32_t count = 0;
    count++;

    // Toggle the LED every .2 second
    if (count == 1)
		{
				// Blue light
				setLEDStatus(false, false, true);
    }
		
		if (count == 2)
		{
				// Green light
				setLEDStatus(false, true, false);
		}
		
		if (count == 9)
		{
				unixTimeSeconds++;
				count = 0;
		}
}

// Check if time is in sync by comparing current time with a known recent timestamp
void timeSyncCheck(uint32_t * unixTimeSeconds)
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
void getTimeAsString(uint32_t unixTimeSeconds, char *timeString)
{
		// Preferred format: HH:MM:SS
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
		
		// Merge strings
		strcat(timeString, hourString);
		strcat(timeString, ":");
		strcat(timeString, minuteString);
		strcat(timeString, ":");
		strcat(timeString, secondString);
}

// Function for converting UnixTimeSeconds to a string
void getDateAsString(uint32_t unixTimeSeconds, char *dateString)
{
		// Preferred format: DD-MM-YYYY
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
		
		// Merge strings
		strcat(dateString, dayString);
		strcat(dateString, "-");
		strcat(dateString, monthString);
		strcat(dateString, "-");
		strcat(dateString, yearString);
}