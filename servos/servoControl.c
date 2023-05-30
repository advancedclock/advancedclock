/*! ***************************************************************************
 *
 * \brief     Servo driver with use of TPM1
 * \file      servoControl.c
 * \author    Jeroen Wijnands
 * \date      May 2023
 *
 * \copyright 
 *
 *\pins PTC1 (SERVO_LEFT), PTC2(RIGHT),	PTC3(LIFT)
 *****************************************************************************/
 
#define SERVO_LEFT 1 									// PTC1 
#define SERVO_LEFT_CHN 0 							// PTC1 = TPM0_CH0

#define SERVO_RIGHT 2 								// PTC2 TPM0_CH1
#define SERVO_RIGHT_CHN 1 						// PTC2 = TPM0_CH1

#define SERVO_LIFT 3 							  	// PTC3 
#define SERVO_LIFT_CHN 2						 	// PTC3 = TPM0_CH2


#include "servoControl.h"

/*!
 * \brief Initialises Timer/PWM Module 1 (SERVO)
 */
void servos_init(void)
{
	//PTC1-3 = TMP0
	//Enable clock to TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0(1);
	//Enable clock to PORTC
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
	
	//Set alternative port function
	PORTC->PCR[SERVO_LEFT] = PORT_PCR_MUX(4);
	PORTC->PCR[SERVO_RIGHT] = PORT_PCR_MUX(4);
	PORTC->PCR[SERVO_LIFT] = PORT_PCR_MUX(4);
	
	
	//prescaler /16
	TPM0->SC = TPM_SC_PS(4);
	
	
	//Module value
	TPM0->MOD = 60000-1;
	
	
	//Enable edge align -> Toggle Output on match
	TPM0->CONTROLS[SERVO_LEFT_CHN].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1);
	TPM0->CONTROLS[SERVO_RIGHT_CHN].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1);
	TPM0->CONTROLS[SERVO_LIFT_CHN].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1);
	
	
	//enable TPM0: LPTPM counter increments on every LPTPM counter clock
	TPM0->SC |= TPM_SC_CMOD(1);		
}


void servoLeftMove(int val)// werkt niet
{
	TPM0->CONTROLS[SERVO_LEFT_CHN].CnV = val;
}

void servoRightMove(int val) // werkt half
{
	TPM0->CONTROLS[SERVO_RIGHT_CHN].CnV = val;
}

void servoLiftMove(int val) // werkt niet
{
	TPM0->CONTROLS[SERVO_LIFT_CHN].CnV = val;
}





