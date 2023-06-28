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
//#define DEBUG

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
#define DISTANCE_FIRST_NAME 4
#define DISTANCE_SECOND_NAME 7
#define DISTANCE_THIRD_NAME 10 
#define DISTANCE_FOURTH_NAME 13

//Reference temp init
#define INIT_REF_TEMP 30

//Time delays
#define HOLD_TIME_SHOW_NAME 5 // 5sec

//includes 
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdio.h>

#include "servoControl.h"
#include "pc_comm.h"
#include "led.h"
#include "delay.h"
#include "clock.h"
#include "lcd_4bit.h"
#include "Temperature.h"
#include "irDistanceSensor.h"

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
void updateTimeSynqStateToPc();
void checkTemperatureStatusAndUpdateToPc();
static bool moveServo = false;
static bool showName(char* out_first_name, char* out_last_name);


/********************************************************************/
/*Varianble definition	 																						*/
/********************************************************************/
datetime_t dateTime;
int prefMinute = 99;
int systemFunction = INIT_SYSTEM;
int referenceTempPrev = 0;
float fTempPrev = 0.0;
bool prevSynqState = false;


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
				
					lcd_clear();
					lcd_printlines("Advanced clock\0","Starting...\0");
					
					SendDebugMsg("Advanced clock starting.\0");
					SendDebugMsg("System init complete.\0");
					systemFunction = PROCESS_PC_DATA;
					break;
				}
				case PROCESS_PC_DATA:
				{			
					processCommData();
					
					if (newUnixTimeAvailable())
					{
						SetUnixTimeClock(GetUnixTime());						
						ProcessedNewUnixTime(true);					
					}					
					
					updateTimeSynqStateToPc();					
					
					systemFunction = WRITE_TIME;
				}				
				case WRITE_TIME:
				{					
					GetDateTime(&dateTime);
					
					if(dateTime.minute != prefMinute)
					{
							prefMinute = dateTime.minute;
						
							SendDebugMsg("Writing time.\0");						
							lcd_printlines("Writing time\0","Please wait...\0");						
							
							writeTime(dateTime.hour ,dateTime.minute);
					}
					systemFunction = UPDATE_DISPLAY;
					break;
				}				

				case UPDATE_DISPLAY:
				{					
					char line1[16] = "\0";	
					char line2[16] = "\0";	
					
					if (showName(line1,line2))//If distancesensor  detecting distance for printing name
					{
						char dbg[50] = "";	
						sprintf(dbg,"Showing name: %s %s\0",line1,line2);										
						SendDebugMsg(dbg);
					}
					else
					{						
						float fTemp  = get_temp_C();//get the float temperature from the sensor
						
						char cSync = '\0';
						char strTime[8] = "\0";
						char strDate[16] = "\0";
						
						GetTimeAsString(&strTime);						
						GetDateAsString(&strDate);
						
						if(ClockOutOfSynq(GetUnixTimeClock()))
							cSync = '!';
						
						sprintf(line1,"%s  %.1f%cC\0",strTime ,fTemp, (char)223);
						sprintf(line2,"%s%c\0", strDate,cSync);															
					}		

					lcd_printlines(line1,line2);				
										
					systemFunction = CHECK_SYSTEM_TEMPERATURE;
					break;
				}
				case CHECK_SYSTEM_TEMPERATURE:
				{				
					checkTemperatureStatusAndUpdateToPc();
					
					systemFunction = PROCESS_PC_DATA;
					break;
				}
			}
    }
}

void initSystem(void)
{	
		//LCD 
		lcd_init();	
	
		//SERVOS
		servos_init();
	
		//TEMPERATURE
		temp_init();
		SetReferenceTemperature(INIT_REF_TEMP);
	
		//IR DISTANCE SENSOR
		ir_init(); 
	
		// init RGB LED
		rgb_init();
	
		// Give PITInit a frequency in Hz for IRQ
		PITInit();
	
		//PC_COMM
		pc_comm_init(); 
		SendDebugMsg("__Init values__\0");
			updateTimeSynqStateToPc();
			SendTemperatureActual(get_temp_C());
			SendTemperatureReference( GetReferenceTemperature());	
		SendDebugMsg("__Init values done__\0");
		
}


void updateTimeSynqStateToPc()
{
		bool clockOutOfSynq = ClockOutOfSynq(GetUnixTimeClock()) ;					
		if(prevSynqState != clockOutOfSynq) 
		{
			prevSynqState = clockOutOfSynq;
			SendTimeSynqState(!clockOutOfSynq);
		}					
}	

void checkTemperatureStatusAndUpdateToPc()
{
	int referenceTemp = GetReferenceTemperature();
	float fTemp  = get_temp_C();	
	bool temperatureToHigh = 	FLOAT_TO_INT(fTemp) >= referenceTemp;			
	bool actualTempChanged = ((fTemp != fTempPrev) && ((fTemp - fTempPrev >= 0.1) || (fTemp - fTempPrev <= -0.1)));//Check if change is bigger then .1 degree
	

	setRedLED(temperatureToHigh);
	setGreenLED(!temperatureToHigh);
	
	//Communicatie with pc app						
	if (actualTempChanged || (referenceTemp != referenceTempPrev))//check for change	
	{		
			fTempPrev = fTemp;
			referenceTempPrev = referenceTemp;
			SendTemperatureActual(fTemp);
			SendTemperatureReference(referenceTemp);
		
			if(temperatureToHigh)
				SendDebugMsg("Temperature to high!\0");			
	}
}

bool showName(char* out_first_name, char* out_last_name)
{
		bool showName = true;
		int distance_cm = getDistanceCm();
	
		if(distance_cm == -1)
		{
				SendErrorMsg("IR ERROR!\0");
				showName = false;
		}
		else if(distance_cm < 1)
		{
				showName = false;
		}
		else if (distance_cm < DISTANCE_FIRST_NAME)
		{
				sprintf(out_first_name,"Anthony\0");
				sprintf(out_last_name,"vd Veght\0");
		}
		else if (distance_cm < DISTANCE_SECOND_NAME)
		{		
				sprintf(out_first_name,"Jaap-Jan\0");
				sprintf(out_last_name,"Groenendijk\0");
		}
		else if (distance_cm < DISTANCE_THIRD_NAME)
		{		
				sprintf(out_first_name,"Jeroen\0");
				sprintf(out_last_name,"Wijnands\0");
		}
		else if (distance_cm < DISTANCE_FOURTH_NAME)
		{
				sprintf(out_first_name,"Koen\0");
				sprintf(out_last_name,"Derksen\0");
		}
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
	sprintf(sVal, "UnixTime: %d\0", GetUnixTime());	
	
	SendDebugMsg(sVal);
}

void echoReferenceTemp(void)
{
	char sVal[50];
	sprintf(sVal, "Ref temp: %d\0", GetReferenceTemperature());	
	
	SendDebugMsg(sVal);
}
#endif
