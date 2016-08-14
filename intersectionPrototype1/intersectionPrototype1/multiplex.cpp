// 
// 
// 

#include "multiplex.h"
#include  <phys253.h>
#include "Arduino.h"
#include "navigation.h"

namespace mux {
	int reading;
	int NEAR_IR_THRESH = 800;
	//this is messy, refactor later if performance issues arise
	double readMUXIn(int muxChip, int channel) {
		switch (muxChip){
		case 1:
			digitalWrite(IR_RESET_1, 1);
			delay(5);
			//get ith bit
			for (int i = 0; i < 3; i++) {
				digitalWrite(MUXOUT_1_PINS[i], bitRead(channel, i));
				//Serial.print(bitRead(inputNum,i));
			}
			
			digitalWrite(IR_RESET_1, 0);
			delay(10);
			reading = analogRead(MUXIN1);

			return reading;
			break;
		case 2:
			digitalWrite(IR_RESET_2, 1);
			//get ith bit
			delay(5);
			for (int i = 0; i < 3; i++) {
				digitalWrite(MUXOUT_2_PINS[i], bitRead(channel, i));
				//Serial.print(bitRead(inputNum,i));
			}
			
			digitalWrite(IR_RESET_2, 0);
			delay(10);
			reading = analogRead(MUXIN2);
			
			return reading;
			break;
		}

		
	}

	int cycleReadIR() {
		int peakSensorID = NULL;
		int maxReading = 300;
		int sensID = 1;
		int read;
		//read MUX 1
		for (const auto &sens : MUX1_IR_CHANNELS) {
			read = readMUXIn(1, sens);
			if ( read > maxReading) {
				peakSensorID = sensID;
				maxReading = read;
			}
			sensID++;
		}

		//read MUX2
		/*
		for (const auto &sens : MUX2_IR_CHANNELS) {
			read = readMUXIn(2, sens);
			if (read > maxReading) {
				peakSensorID = sensID;
				maxReading = read;
			}
			sensID++;
		}
		*/
		if (peakSensorID == 1 || peakSensorID == 2) {
			return LEFT;
		}
		else if (peakSensorID == 3 || peakSensorID == 4) {
			return STRAIGHT;
		}
		else if (peakSensorID == 5 || peakSensorID == 6) {
			return RIGHT;
		}
		else {
			return NONE;
		}
		/*int peakSensorID = NONE;
		int maxReading = 200;
		const int AVG_MULTIPLIER_THRESH = 1.5;
		int sensID = 1;
		int avread = 0;
		int read[6];
		//read MUX 1
		for (int i = 0; i < 6; i++) {
			read[i] = readMUXIn(1, MUX1_IR_CHANNELS[i]);
			avread += read[i];
			if (read[i] > maxReading) {
				peakSensorID = sensID;
				maxReading = read[i];
			}
			
			sensID++;
		}
		avread  = (avread - maxReading)/5;
		if (maxReading < (AVG_MULTIPLIER_THRESH * avread)) {
			peakSensorID = NONE;
		}

		if (peakSensorID == 1 || peakSensorID == 2) {
			return LEFT;
		}
		else if (peakSensorID == 3 || peakSensorID == 4) {
			return STRAIGHT;
		}
		else if (peakSensorID == 5 || peakSensorID == 6) {
			return RIGHT;
		}
		else {
			return NONE;
		}
*/

	}

	//TODO: add threshold as parameter in future
	//also consider averaging because of noise
	int detectAdjacentPassenger() {
		
		int nearIR_RR = readMUXIn(2, NEAR_IR_RIGHT);
		int nearIR_RL = readMUXIn(2, NEAR_IR_LEFT);

		//right near IR sensor
		if ( nearIR_RR > NEAR_IR_THRESH) {
			return RIGHT;
		}

		//left near IR sensor
		else if (nearIR_RL > NEAR_IR_THRESH) {
			return LEFT;
		}

		else {
			return NONE;
		}
	}
}

