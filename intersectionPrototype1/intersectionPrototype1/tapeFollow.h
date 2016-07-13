// tapeFollow.h

#ifndef _TAPEFOLLOW_h
#define _TAPEFOLLOW_h

/*
	(relatively) Successful configurations:
	July 12: p = 10, d = 14, fspeed = 60, tspeed = +/- 55
	July 12: p = 10, d = 7, fspeed = 70, tspeed = +/- 55 (may be unreliable near the roundabout)
*/
//constants
#define TD_L 1
#define TD_R 2

#define ID_R 3
#define ID_L 0

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
	extern int error;
	void followTape(int motorSpeed);
	void turnLeft();
	void turnRight();
	double getKp();
	double getKd();



	
}
	



#endif
