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

void servoLeftMove(int);

void servoRightMove(int);

void servoLiftMove(int);



#endif // SERVO_CONTROL_H
