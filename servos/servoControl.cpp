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

/*******************************************************************************/
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
/********************************************************************/

#include <Servo-1.2.0/src/Servo.h>
#include <Time/TimeLib.h>
#include <math.h>


#include "servoControl.h"
#include "ServoConfig.h"

static int servoLift = LIFTSPEED;
static volatile double lastX = 75;
static volatile double lastY = 47.5;

static int last_min = 0;


/*!
 * \brief Initialises Timer/PWM Module 1 (SERVO)
 */
void servos_init(void)
{
	configServoHW();
}

void setup()
{
    setTime(19, 38, 0, 0, 0, 0);

    drawTo(75.2, 47);
    lift(0);
}

void loop(void)
{

#ifdef CALIBRATION

    // Servohorns will have 90? between movements, parallel to x and y axis
    drawTo(-3, 29.2);
    delay(500);
    drawTo(74.1, 28);
    delay(500);

#else 


    int i = 0;
    if (last_min != minute()) {

        lift(0);

        hour();
        while ((i + 1) * 10 <= hour())
        {
            i++;
        }

        number(3, 3, 111, 1);
        number(5, 25, i, 0.9);
        number(19, 25, (hour() - i * 10), 0.9);
        number(28, 25, 11, 0.9);

        i = 0;
        while ((i + 1) * 10 <= minute())
        {
            i++;
        }
        number(34, 25, i, 0.9);
        number(48, 25, (minute() - i * 10), 0.9);
        lift(2);
        drawTo(74.2, 47.5);
        lift(1);
        last_min = minute();

    }

#endif

}

// Writing numeral with bx by being the bottom left originpoint. Scale 1 equals a 20 mm high font.
// The structure follows this principle: move to first startpoint of the numeral, lift down, draw numeral, lift up
void number(float bx, float by, int num, float scale) {

    switch (num) {

    case 0:
        drawTo(bx + 12 * scale, by + 6 * scale);
        lift(0);
        bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
        lift(1);
        break;
    case 1:

        drawTo(bx + 3 * scale, by + 15 * scale);
        lift(0);
        drawTo(bx + 10 * scale, by + 20 * scale);
        drawTo(bx + 10 * scale, by + 0 * scale);
        lift(1);
        break;
    case 2:
        drawTo(bx + 2 * scale, by + 12 * scale);
        lift(0);
        bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
        drawTo(bx + 1 * scale, by + 0 * scale);
        drawTo(bx + 12 * scale, by + 0 * scale);
        lift(1);
        break;
    case 3:
        drawTo(bx + 2 * scale, by + 17 * scale);
        lift(0);
        bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
        bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
        lift(1);
        break;
    case 4:
        drawTo(bx + 10 * scale, by + 0 * scale);
        lift(0);
        drawTo(bx + 10 * scale, by + 20 * scale);
        drawTo(bx + 2 * scale, by + 6 * scale);
        drawTo(bx + 12 * scale, by + 6 * scale);
        lift(1);
        break;
    case 5:
        drawTo(bx + 2 * scale, by + 5 * scale);
        lift(0);
        bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
        drawTo(bx + 5 * scale, by + 20 * scale);
        drawTo(bx + 12 * scale, by + 20 * scale);
        lift(1);
        break;
    case 6:
        drawTo(bx + 2 * scale, by + 10 * scale);
        lift(0);
        bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
        drawTo(bx + 11 * scale, by + 20 * scale);
        lift(1);
        break;
    case 7:
        drawTo(bx + 2 * scale, by + 20 * scale);
        lift(0);
        drawTo(bx + 12 * scale, by + 20 * scale);
        drawTo(bx + 2 * scale, by + 0);
        lift(1);
        break;
    case 8:
        drawTo(bx + 5 * scale, by + 10 * scale);
        lift(0);
        bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
        bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
        lift(1);
        break;

    case 9:
        drawTo(bx + 9 * scale, by + 11 * scale);
        lift(0);
        bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
        drawTo(bx + 5 * scale, by + 0);
        lift(1);
        break;

    case 111:

        lift(0);
        drawTo(70, 46);
        drawTo(65, 43);

        drawTo(65, 49);
        drawTo(5, 49);
        drawTo(5, 45);
        drawTo(65, 45);
        drawTo(65, 40);

        drawTo(5, 40);
        drawTo(5, 35);
        drawTo(65, 35);
        drawTo(65, 30);

        drawTo(5, 30);
        drawTo(5, 25);
        drawTo(65, 25);
        drawTo(65, 20);

        drawTo(5, 20);
        drawTo(60, 44);

        drawTo(75.2, 47);
        lift(2);

        break;

    case 11:
        drawTo(bx + 5 * scale, by + 15 * scale);
        lift(0);
        bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
        lift(1);
        drawTo(bx + 5 * scale, by + 5 * scale);
        lift(0);
        bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
        lift(1);
        break;

    }
}



void lift(char lift) {
    switch (lift) {
        // room to optimize  !

    case 0: //850

        if (servoLift >= LIFT0) {
            while (servoLift >= LIFT0)
            {
                servoLift--;
                servoLiftMove(servoLift);
               // delayMicroseconds(LIFTSPEED);
            }
        }
        else {
            while (servoLift <= LIFT0) {
                servoLift++;
                servoLiftMove(servoLift);
                //delayMicroseconds(LIFTSPEED);

            }

        }

        break;

    case 1: //150

        if (servoLift >= LIFT1) {
            while (servoLift >= LIFT1) {
                servoLift--;
                servoLiftMove(servoLift);
                //delayMicroseconds(LIFTSPEED);

            }
        }
        else {
            while (servoLift <= LIFT1) {
                servoLift++;
                servoLiftMove(servoLift);
                //delayMicroseconds(LIFTSPEED);
            }

        }

        break;

    case 2:

        if (servoLift >= LIFT2) {
            while (servoLift >= LIFT2) {
                servoLift--;
                servoLiftMove(servoLift);
                //delayMicroseconds(LIFTSPEED);
            }
        }
        else {
            while (servoLift <= LIFT2) {
                servoLift++;
                servoLiftMove(servoLift);
                //delayMicroseconds(LIFTSPEED);
            }
        }
        break;
    }
}


void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
    float inkr = -0.05;
    float count = 0;

    do {
        drawTo(sqee * radius * cos(start + count) + bx,
            radius * sin(start + count) + by);
        count += inkr;
    } while ((start + count) > ende);

}

void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
    float inkr = 0.05;
    float count = 0;

    do {
        drawTo(sqee * radius * cos(start + count) + bx,
            radius * sin(start + count) + by);
        count += inkr;
    } while ((start + count) <= ende);
}


void drawTo(double pX, double pY) {
    double dx, dy, c;
    int i;

    // dx dy of new point
    dx = pX - lastX;
    dy = pY - lastY;
    //path lenght in mm, times 4 equals 4 steps per mm
    c = floor(4 * sqrt(dx * dx + dy * dy));

    if (c < 1) c = 1;

    for (i = 0; i <= c; i++) {
        // draw line point by point
        set_XY(lastX + (i * dx / c), lastY + (i * dy / c));

    }

    lastX = pX;
    lastY = pY;
}

double return_angle(double a, double b, double c) {
    // cosine rule for angle between c and a
    return acos((a * a + c * c - b * b) / (2 * a * c));
}

void set_XY(double Tx, double Ty)
{
    //delay(1);
    double dx, dy, c, a1, a2, Hx, Hy;

    // calculate triangle between pen, servoLeft and arm joint
    // cartesian dx/dy
    dx = Tx - O1X;
    dy = Ty - O1Y;

    // polar lemgth (c) and angle (a1)
    c = sqrt(dx * dx + dy * dy); // 
    a1 = atan2(dy, dx); //
    a2 = return_angle(L1, L2, c);

    servoLeftMove(floor(((a2 + a1 - M_PI) * SERVOFAKTORLEFT) + SERVOLEFTNULL));

    // calculate joinr arm point for triangle of the right servo arm
    a2 = return_angle(L2, L1, c);
    Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5?
    Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

    // calculate triangle between pen joint, servoRight and arm joint
    dx = Hx - O2X;
    dy = Hy - O2Y;

    c = sqrt(dx * dx + dy * dy);
    a1 = atan2(dy, dx);
    a2 = return_angle(L1, (L2 - L3), c);

    servoRightMove(floor(((a1 - a2) * SERVOFAKTORRIGHT) + SERVORIGHTNULL));

}

/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
static void configServoHW(void)
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





