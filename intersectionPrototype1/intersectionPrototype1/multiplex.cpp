// 
// 
// 

#include "multiplex.h"
#include  <phys253.h>
#include "Arduino.h"

namespace mux {
	int reading;
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
		int maxReading = 30;
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
		for (const auto &sens : MUX2_IR_CHANNELS) {
			read = readMUXIn(2, sens);
			if (read > maxReading) {
				peakSensorID = sensID;
				maxReading = read;
			}
			sensID++;
		}

		return peakSensorID;
	}
}

