/*! ***************************************************************************
 *
 * \brief     Servo configuration
 * \file      servoControl.h
 * \author    
 * \date      May 2023
 *
 * \copyright 
 *****************************************************************************/
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

// delete or mark the next line as comment if you don't need these
//#define CALIBRATION      // enable calibration mode
//#define REALTIMECLOCK    // enable real time clock

// When in calibration mode, adjust the following factor until the servos move exactly 90 degrees
#define SERVOFAKTORLEFT 650
#define SERVOFAKTORRIGHT 650

// Zero-position of left and right servo
// When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
// either to the X or Y axis
#define SERVOLEFTNULL 2280
#define SERVORIGHTNULL 860//920

//3, 5, 6, 9, 10, 11
#define SERVOPINLIFT  3//D3//2
#define SERVOPINLEFT  6//D6//3
#define SERVOPINRIGHT 5//D5//4

// lift positions of lifting servo
#define LIFT0 1080 // on drawing surface
#define LIFT1 925  // between numbers
#define LIFT2 725  // going towards sweeper

// speed of liftimg arm, higher is slower
#define LIFTSPEED 1500

// length of arms
#define L1 35
#define L2 55.1
#define L3 13.2

// origin points of left and right servo 
#define O1X 22
#define O1Y -25
#define O2X 47
#define O2Y -25


#endif 