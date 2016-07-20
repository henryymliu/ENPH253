// tapeFollow.h

#ifndef _TAPEFOLLOW_h
#define _TAPEFOLLOW_h

/*
	(relatively) Successful configurations:
	July 12: p = 10, d = 14, fspeed = 60, tspeed = +/- 55
	July 12: p = 10, d = 7, fspeed = 70, tspeed = +/- 55 (may be unreliable near the roundabout)

	July 19th: p = 16, d = 23, fspeed = 70, tspeed = +/-55
*/
//constants
#define TD_L 1
#define TD_R 0

#define ID_R 4
#define ID_L 5

#define KP_KNOB 6
#define KD_KNOB 7

#define L_MOTOR 1
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
	extern volatile int error; //volatile so ISR may modify it after U-turn
	extern bool intersectionDetected;
	void followTape(int motorSpeed);
	void turnLeft();
	void turnRight();
	void turnAround();
	double getKp();
	double getKd();

	
}
	



#endif
