// armControl.h

#ifndef _ARMCONTROL_h
#define _ARMCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace arm {
	//pickup functions
	void turn_arm(int angle);
	void extend_grab();
	void retract();
	void grab();
	void release();
	
	void pickup(int dir);

	//rotary encoder stuffs
	struct motorEncoder {
		int encoderPinR;
		int encoderPinL;
		//resets to position 0 on startup
		int rotaryPosition = 0;

		int state = 0;
		bool rightState;
		bool leftState;

		motorEncoder(int eP1, int eP2) : encoderPinR(eP1), encoderPinL(eP2){}

		//Returns encoder position, from 0 to 24.
		//Inputs:
		// encoderPinR, encoderPinL are digital pins of right and left encoder pin respectively
		//	
		double readEncoderAngle();
	};

	const int tt_ePR = 1;
	const int tt_ePL = 2;
	const int aa_ePR = 3;
	const int aa_ePL = 4;
	extern motorEncoder turntable; 
	extern motorEncoder armActuator;

	double turntableAngle(motorEncoder tt);
}


#endif

