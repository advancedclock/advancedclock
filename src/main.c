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
 *             
 *            
 *            
 *            
 *
 *****************************************************************************/
 #define DEBUG
 
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdio.h>

#include "servoControl.h"
#include "pc_comm.h"


//Debug function proto
void echoUnixTime(void);
void echoReferenceTemp(void);

// Local function prototypes
static void delay_us(uint32_t d);
void rgb_init(void);
void rgb_onoff(const bool r, const bool g, const bool b);
static bool moveServo = false;

/*!
 * \brief Main application
 */
int main(void)
{
		//RGB
   // rgb_init();
		//rgb_onoff(true, true, true);
		delay_us(500000);
		//rgb_onoff(false, false, false);
	
		//PC_COMM
		pc_comm_init();  
		
	
		//SERVOS
		servos_init();

    while(1)
    {
			SendDebugMsg("Advanced clock alive\r\n");
			processCommData();

      delay_us(1000000);
			
			
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
			
			
			
			//Toggle servo position
			moveServo? servoLeftMove(4000):servoLeftMove(6000);			
			moveServo? servoRightMove(4000):servoRightMove(6000);
			moveServo? servoLiftMove(4000):servoLiftMove(6000);
			moveServo =! moveServo;
		
			 
    }
}
	

/*!
 * \brief Creates a blocking delay
 *
 * Software delay of approximately 1.02 us, depending on compiler version,
 * CPU clock frequency and optimizations.
 * - C compiler: ARMClang v6
 * - Language C: gnu11
 * - CPU clock: 48 MHz
 * - Optimization level: -O3
 * - Link-Time Optimization: disabled
 *
 * \param[in]  d  delay in microseconds
 */
static void delay_us(uint32_t d)
{

#if (CLOCK_SETUP != 1)
#warning This delay function does not work as designed
#endif

    volatile uint32_t t;

    for(t=4*d; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
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
