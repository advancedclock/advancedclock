/*! ***************************************************************************
 *
 * \brief     Advanced clock
 * \file      main.c
 * \author    Anthony_Jaap-Jan_Jeroen_Koen
 * \date      May 2023
 *
 * \copyright 
 *Anthony
 *Jaap-Jan
 *Jeroen
 *Koen
 *
 *****************************************************************************/

#define DEBUG

#define INIT_SYSTEM 0
#define PROCESS_PC_DATA 1
#define UPDATE_DISPLAY 2
#define WRITE_TIME 3

 
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdio.h>

#include "servoControl.h"
#include "pc_comm.h"
#include "led.h"
#include "delay.h"
#include "clock.h"

//Debug function proto
void echoUnixTime(void);
void echoReferenceTemp(void);

// Local function prototypes
void init(void);
void delay_us(uint32_t d);
void rgb_init(void);
void rgb_onoff(const bool r, const bool g, const bool b);
static bool moveServo = false;

datetime_t dateTime;
int prefMinute = 99;
int function = 0;

/*!
 * \brief Main application
 */
int main(void)
{
    while(1)
    {			
			
			switch(function)
			{
				case INIT_SYSTEM:
				{
					init();	
					SendDebugMsg("System init complete\r\n");
					function = PROCESS_PC_DATA;
					break;
				}
				case PROCESS_PC_DATA:
				{
					processCommData();
					function = WRITE_TIME;
				}
				case UPDATE_DISPLAY:
				{
					GetDateTime(&dateTime);
					break;
				}
				case WRITE_TIME:
				{
					GetDateTime(&dateTime);
					if(dateTime.minute != prefMinute)
					{
							prefMinute = dateTime.minute;
							writeTime(dateTime.hour ,dateTime.minute);
					}
					function = PROCESS_PC_DATA;
					break;
				}
			}
			
			
			#ifdef DEBUG
				echoUnixTime();
				echoReferenceTemp();
				
				SendErrorMsg("test!");
				SendTemperatureActual(25);
				SendTemperatureReference(GetReferenceTemperature());
				
				if(GetUnixTime() > 0)
					SendTimeSynqState(true);
				else
					SendTimeSynqState(false);
			#endif
			 delay_us(1000000); // 1 sec		
    }
}

void init(void)
{
		//PC_COMM
		pc_comm_init();  	
	
		//SERVOS
		servos_init();
		
		// init RGB LED
		//rgb_init();
	
		// Give PITInit a frequency in Hz for IRQ
		//PITInit(10);
}
/********************************************************/
/*DEBUG FUNCTIONS																				*/
/********************************************************/
#ifdef DEBUG
void echoUnixTime(void)
{
	char sVal[50];
	sprintf(sVal, "UnixTime: %d\r\n", GetUnixTime());	
	
	SendDebugMsg(sVal);
}

void echoReferenceTemp(void)
{
	char sVal[50];
	sprintf(sVal, "Ref temp: %d\r\n", GetReferenceTemperature());	
	
	SendDebugMsg(sVal);
}
#endif
