// multiplex.h

#ifndef _MULTIPLEX_h
#define _MULTIPLEX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//This library is used for handling multiplexing and especially IR signals.
//Note: Port 1 of digital pins on TINAH (pins 8-15) configured to be digital out
namespace mux {
	//enum DIRECTION { LEFT = 0, STRAIGHT = 1, RIGHT = 2, BACK = -1, NONE = -2 };

	//MUX 1 is far range, MUX 2 is close range
	//IR sensor channels, indexed 1-6, left to right, across multiplexers
	const int MUX1_IR_CHANNELS[] = {6,4,3,0,1,2}; //left IR
	//const int MUX2_IR_CHANNELS[] = {3,0,1}; //right IR


	//near IR params, ALL TEMPORARY FOR NOW
	const int NEAR_IR_LEFT = 3;
	const int NEAR_IR_RIGHT = 2;
	extern int NEAR_IR_THRESH;

	//IR digital outs
	const int MUXOUT_1_PINS[] = { 11,9,10};
	const int MUXOUT_2_PINS[] = { 15,14,13};

	const int IR_RESET_1 = 8;
	const int IR_RESET_2 = 12;

	//IR analog in
	const int MUXIN1 = 1;
	const int MUXIN2 = 0;

	//reads one channel of multiplexer, returns analogRead value
	double readMUXIn(int muxChip, int channel);

	//reads through all IR detector sensors (not the ones next to the turntable) and returns ID of IR sensor
	//with strongest signal
	int cycleReadIR();

	//checks side IR (next to arm) to check for passenger
	//TODO: calibrate short range IR to go close to 5 V when next to passenger
	//returns LEFT or RIGHT depending on which IR sensor detects passenger, NONE if no adjacent passenger detected
	//function should be run in main loop
	int detectAdjacentPassenger();



}

#endif

