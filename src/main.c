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
#define DISTANCE_FIRST_NAME 4
#define DISTANCE_SECOND_NAME 7
#define DISTANCE_THIRD_NAME 10 
#define DISTANCE_FOURTH_NAME 13

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
static bool moveServo = false;
static bool showName(char* out_first_name, char* out_last_name);

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
				
					lcd_clear();
					lcd_printlines("Advanced clock\0","Starting...\0");
					
					SendDebugMsg("System init complete\r\n");
					systemFunction = PROCESS_PC_DATA;
					break;
				}
				case PROCESS_PC_DATA:
				{
					processCommData();
					
					if (newUnixTimeAvailable())
					{
						//setTime(); todo
						ProcessedNewUnixTime(true);
						SendTimeSynqState(true);						
					}
					systemFunction = WRITE_TIME;
				}				
				case WRITE_TIME:
				{					
					GetDateTime(&dateTime);
					if(dateTime.minute != prefMinute)
					{
							prefMinute = dateTime.minute;
						
							lcd_printlines("Writing time\0","Please wait...\0");
						
							//writeTime(dateTime.hour ,dateTime.minute);
					}
					systemFunction = UPDATE_DISPLAY;
					break;
				}				

				case UPDATE_DISPLAY:
				{					
					/*const char line1[16] = "Distance\0"; 		// Value for test
					const char line2[16] = "\0";	// Value for test	
					
					int distance_cm = getDistanceCm();//irReadDistance();
					
					
					sprintf(line2, "%d", distance_cm);
					lcd_printlines(line1,line2);
					
					showName(&line1,&line2);
					
					systemFunction = UPDATE_DISPLAY;
					break;*/
					
					///////////////////////////////////////////////////////////////////
					
					
					const char line1[16] = ""; 		// Value for test
					const char line2[16] = "";	// Value for test				
					
					if (!showName(line1,line2))
					{
						sprintf(line1,"12:34:56\0");
						sprintf(line1,"1 Mei 2023\0");							
					}		
					
					SendDebugMsg(line1);
					SendDebugMsg(line2);
					
					lcd_printlines(line1,line2);				
					
					
					systemFunction = CHECK_SYSTEM_TEMPERATURE;
					break;
				}
				case CHECK_SYSTEM_TEMPERATURE:
				{
					const char line1[16] = "Temperature";
			    const char line2[16] = "";
					
					float fTemp  = get_temp_C();//get the float temperature from the sensor
					
					int iTemp = FLOAT_TO_INT(fTemp); 
					int referenceTemp = GetReferenceTemperature();
							
					//Update display
					sprintf(line2, "%.2f %cC", fTemp, (char)223);//print the float temperature in string 
					lcd_printlines(line1,line2);						
					
					//Check actual temp exceeds reference temp
					if(iTemp >= referenceTemp)
					{
						//setLEDStatus(true,false,false);//RED
					}
					else
					{
						//setLEDStatus(false,true,false);//GREEN
					}
					
					//Communicatie with pc app					
					SendTemperatureActual(fTemp);
					SendTemperatureReference(referenceTemp);
					
					systemFunction = PROCESS_PC_DATA;
					break;
				}
			}
			
			
			/*#ifdef DEBUG
				echoUnixTime();
				echoReferenceTemp();
				
				SendTemperatureReference(GetReferenceTemperature());
				
				if(GetUnixTime() > 0)
					SendTimeSynqState(true);
				else
					SendTimeSynqState(false);
			#endif*/
			delay_us(500000); // 1 sec	Wat hiermee doen?	
    }
}

void initSystem(void)
{	
		//LCD 
		lcd_init();	
	
		//PC_COMM
		pc_comm_init();  	
	
		//SERVOS
		servos_init();
	
		//TEMPERATURE
		temp_init();
	
		//IR DISTANCE SENSOR
		ir_init();  
	
		// init RGB LED
		//rgb_init();
	
		// Give PITInit a frequency in Hz for IRQ
		//PITInit(10);
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
				sprintf(out_first_name,"Anthony");
				sprintf(out_last_name,"vd Veght");
		}
		else if (distance_cm < DISTANCE_SECOND_NAME)
		{		
				sprintf(out_first_name,"Jaap-Jan");
				sprintf(out_last_name,"Groenendijk");
		}
		else if (distance_cm < DISTANCE_THIRD_NAME)
		{		
				sprintf(out_first_name,"Jeroen");
				sprintf(out_last_name,"Wijnands");
		}
		else if (distance_cm < DISTANCE_FOURTH_NAME)
		{
				sprintf(out_first_name,"Koen");
				sprintf(out_last_name,"Derksen");
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
