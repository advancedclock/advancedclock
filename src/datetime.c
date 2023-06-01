// The functions in this file were copied from the Kinetis SDK v1.3.0.
/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#include "datetime.h"
#define SECONDS_IN_A_DAY (86400U)
#define SECONDS_IN_A_HOUR (3600U)
#define SECONDS_IN_A_MIN (60U)
#define MINS_IN_A_HOUR (60U)
#define HOURS_IN_A_DAY (24U)
#define DAYS_IN_A_YEAR (365U)
#define DAYS_IN_A_LEAP_YEAR (366U)
#define YEAR_RANGE_START (1970U)
#define YEAR_RANGE_END (2099U)
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Table of month length (in days) for the Un-leap-year*/
static const uint8_t ULY[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
							  31U, 30U, 31U};
/* Table of month length (in days) for the Leap-year*/
static const uint8_t LY[] = {0U, 31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
							 31U, 30U, 31U};
/* Number of days from begin of the non Leap-year*/
static const uint16_t MONTH_DAYS[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U,
									  212U, 243U, 273U, 304U, 334U};
/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_ConvertSecsToDatetime
 * Description : converts time data from seconds to a datetime structure.
 * This function will convert time data from seconds to a datetime structure.
 *
 *END**************************************************************************/
void RTC_HAL_ConvertSecsToDatetime(const uint32_t *seconds, datetime_t *datetime)
{
	uint32_t x;
	uint32_t Seconds, Days, Days_in_year;
	const uint8_t *Days_in_month;
	/* Start from 1970-01-01*/
	Seconds = *seconds;
	/* days, we add 1 for the current day which is represented in the hours and seconds field */
	Days = Seconds / SECONDS_IN_A_DAY + 1;
	/* seconds left*/
	Seconds = Seconds % SECONDS_IN_A_DAY;
	/* hours*/
	datetime->hour = Seconds / SECONDS_IN_A_HOUR;
	/* seconds left*/
	Seconds = Seconds % SECONDS_IN_A_HOUR;
	/* minutes*/
	datetime->minute = Seconds / SECONDS_IN_A_MIN;
	/* seconds*/
	datetime->second = Seconds % SECONDS_IN_A_MIN;
	/* year*/
	datetime->year = YEAR_RANGE_START;
	Days_in_year = DAYS_IN_A_YEAR;
	while (Days > Days_in_year)
	{
		Days -= Days_in_year;
		datetime->year++;
		if (datetime->year & 3U)
		{
			Days_in_year = DAYS_IN_A_YEAR;
		}
		else
		{
			Days_in_year = DAYS_IN_A_LEAP_YEAR;
		}
	}
	if (datetime->year & 3U)
	{
		Days_in_month = ULY;
	}
	else
	{
		Days_in_month = LY;
	}
	for (x = 1U; x <= 12U; x++)
	{
		if (Days <= (*(Days_in_month + x)))
		{
			datetime->month = x;
			break;
		}
		else
		{
			Days -= (*(Days_in_month + x));
		}
	}
	datetime->day = Days;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : RTC_HAL_ConvertDatetimeToSecs
 * Description : converts time data from datetime to seconds.
 * This function will convert time data from datetime to seconds.
 *
 *END**************************************************************************/
void RTC_HAL_ConvertDatetimeToSecs(const datetime_t *datetime, uint32_t *seconds)
{
	/* Compute number of days from 1970 till given year*/
	*seconds = (datetime->year - 1970U) * DAYS_IN_A_YEAR;
	/* Add leap year days */
	*seconds += ((datetime->year / 4) - (1970U / 4));
	/* Add number of days till given month*/
	*seconds += MONTH_DAYS[datetime->month];
	/* Add days in given month. We take away seconds for the current day as it is
	 * represented in the hours and seconds field*/
	*seconds += (datetime->day - 1);
	/* For leap year if month less than or equal to Febraury, decrement day counter*/

	if ((!(datetime->year & 3U)) && (datetime->month <= 2U))
	{
	}

	*seconds = ((*seconds) * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
			   (datetime->minute * SECONDS_IN_A_MIN) + datetime->second;
}
