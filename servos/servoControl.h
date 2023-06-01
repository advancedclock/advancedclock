/*! ***************************************************************************
 *
 * \brief     Servo driver for TPM1
 * \file      servoControl.h
 * \author    
 * \date      May 2023
 *
 * \copyright 
 *****************************************************************************/
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H


#include <MKL25Z4.h>


void servos_init(void);
void loop(void);
void servoLeftMove(double);
void servoRightMove(double);
void servoLiftMove(double);



/*test functions*/
void setTime(int hour, int minute);
int hour(void);
int minute(void);



#endif // SERVO_CONTROL_H
