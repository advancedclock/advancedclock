/*! ***************************************************************************
 *
 * \brief     Advanced clock
 * \file      main.c
 * \author    Anthony, Jaap-Jan, Jeroen, Koen
 * \date      May 2023
 *
 * \copyright 
 *Anthony
 *Jaap-Jan
 *Jeroen
 *Koen
 *****************************************************************************/
//Uncomment for debugging
#define DEBUG

//Converter
#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

//system functions
#define INIT_SYSTEM 0
#define PROCESS_PC_DATA 1
#define WRITE_TIME 2
#define UPDATE_DISPLAY 3
#define READ_DISTANCE 4
#define CHECK_SYSTEM_TEMPERATURE 5

//Name distance config in cm
#define DISTANCE_FIRST_NAME 10
#define DISTANCE_SECOND_NAME 15
#define DISTANCE_THIRD_NAME 20 
#define DISTANCE_FOURTH_NAME 25

//includes 
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdio.h>

#include "servoControl.h"
#include "pc_comm.h"
#include "led.h"
#include "delay.h"
#include "clock.h"

/********************************************************************/
/*Function prototypes  	 																						*/
/********************************************************************/
//Debug function prototypes
void echoUnixTime(void);
void echoReferenceTemp(void);

// Local function prototypes
void initSystem(void);
void delay_us(uint32_t d);
void rgb_init(void);
void rgb_onoff(const bool r, const bool g, const bool b);
static bool moveServo = false;
static bool showName(char* out_name);

/********************************************************************/
/*Varianble definition	 																						*/
/********************************************************************/
datetime_t dateTime;
int prefMinute = 99;
int systemFunction = INIT_SYSTEM;

/********************************************************************/
/*Functions							 																						*/
/********************************************************************/
int main(void)
{
    while(true)
    {						
			switch(systemFunction)
			{
				case INIT_SYSTEM:
				{
					initSystem();	
					SendDebugMsg("System init complete\r\n");
					systemFunction = PROCESS_PC_DATA;
					break;
				}
				case PROCESS_PC_DATA:
				{
					processCommData();
					systemFunction = WRITE_TIME;
				}				
				case WRITE_TIME:
				{
					//UpdateDisplay("Writing","time");
					GetDateTime(&dateTime);
					if(dateTime.minute != prefMinute)
					{
							prefMinute = dateTime.minute;
							writeTime(dateTime.hour ,dateTime.minute);
					}
					systemFunction = UPDATE_DISPLAY;
					break;
				}				

				case UPDATE_DISPLAY:
				{					
					char line1[16];
					char line2[16];
					
					if (!showName(line1))
					{
							//getTimeAsString(line1);
							//getDateAsString(line2);
					}
					//UpdateDisplay(line1,line2);
					
					systemFunction = CHECK_SYSTEM_TEMPERATURE;
					break;
				}
				case CHECK_SYSTEM_TEMPERATURE:
				{
					int temp = 0;//FLOAT_TO_INT(get_temp_C());
					if(temp >= GetReferenceTemperature())
					{
						//setLEDStatus(true,false,false);//RED
					}
					else
					{
						//setLEDStatus(false,true,false);//GREEN
					}
						
					systemFunction = PROCESS_PC_DATA;
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
			delay_us(1000000); // 1 sec	Wat hiermee doen?	
    }
}

void initSystem(void)
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


bool showName(char* out_name)
{
		bool showName = true;
		int distance_cm = 1000;//irReadDistance();
	
		if(distance_cm = -1)
				out_name = "IR ERROR!\0";

		else if (distance_cm < DISTANCE_FIRST_NAME)
				out_name = "Anthony\0";
		
		else if (distance_cm < DISTANCE_SECOND_NAME)
				out_name = "Jaap-Jan\0";
		
		else if (distance_cm < DISTANCE_THIRD_NAME)
				out_name = "Jeroen\0";
		
		else if (distance_cm < DISTANCE_FOURTH_NAME)
				out_name = "Koen\0";
		
		else
				showName = false;
		
		return showName;			
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
