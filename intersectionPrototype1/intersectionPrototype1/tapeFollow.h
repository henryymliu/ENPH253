// tapeFollow.h

#ifndef _TAPEFOLLOW_h
#define _TAPEFOLLOW_h

/*
	(relatively) Successful configurations:
	July 20th: p = 8, d = 9, fspeed = 80, tspeed = +/-55
*/
//constants
#define TD_L 4
#define TD_R 3

#define ID_R 2
#define ID_L 5

#define KP_KNOB 6
#define KD_KNOB 7

#define L_MOTOR 3
#define R_MOTOR 0

#define INTERSECTION_TURNING_DELAY_MILLI 400
#define INTERSECTION_TURNING_DEADZONE 1000

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


namespace tapeFollow{

	//int motorSpeed = 500;
	extern int error; //volatile so ISR may modify it after U-turn
	extern bool intersectionDetected;
	extern bool collision;
	extern bool dropoff;
	void followTape(int motorSpeed);
	void turnLeft();
	void turnRight();
	void turnAround();
	extern int c;

	
}
	

#endif
