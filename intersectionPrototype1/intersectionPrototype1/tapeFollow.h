// tapeFollow.h

#ifndef _TAPEFOLLOW_h
#define _TAPEFOLLOW_h

//constants
#define TD_L 2
#define TD_R 1

#define ID_R 3
#define ID_L 0

#define KP_KNOB 6
#define KD_KNOB 7

#define L_MOTOR 0
#define R_MOTOR 3

#define INTERSECTION_TURNING_DELAY_MILLI 500
#define INTERSECTION_TURNING_DEADZONE 1000

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class tapeFollow{
public:
	//int motorSpeed = 500;
	int error;
	void followTape(int motorSpeed);
	void turnLeft();
	void turnRight();

private:
	double kp;
	double kd;
	double gain;
	int thresh;

	int left;
	int right;

	int lerr = 0;
	int recerr = 0;
	int c = 0;

	double p;
	double d;
	double cons;
	int m = 1;
	int q;

	int intersectLeft;
	int intersectRight;
	unsigned long currTime;
};
	



#endif
