/*! ***************************************************************************
 *
 * \brief     Servo driver for TPM1
 * \file      servoControl.h
 * \author    
 * \date      May 2023
 *
 * \copyright Jeroen Wijnands
 *****************************************************************************/
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H


#include <MKL25Z4.h>


void servos_init(void);
void callibrate(void);
void writeTime(int hour, int minute);


#endif // SERVO_CONTROL_H
