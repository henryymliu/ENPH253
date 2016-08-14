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
	void turn_arm(int pos);
	void turn_actuator(int pos);
	void extend();
	void extend_grab();
	void retract();
	void grab();
	void release();
	void stow();
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

	const int tt_ePR = 2;
	const int tt_ePL = 3;
	const int aa_ePR = 6;
	const int aa_ePL = 7;
	extern motorEncoder turntable; 
	extern motorEncoder armActuator;

	const int TILTSERVO_PICKUP_ANGLE = 165;
	const int TILTSERVO_STOW_ANGLE = 110;
	double turntableAngle(motorEncoder tt);
}


#endif

