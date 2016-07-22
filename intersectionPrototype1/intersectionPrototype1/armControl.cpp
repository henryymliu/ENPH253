// 
// 
// 

#include "armControl.h"
#include "Arduino.h"
#include "phys253.h"

#define PICKUP_SWITCH 0
#define ACTUATOR 0
#define ACTUATOR_SPEED 50
#define PICKUP_DELAY 3000
int time;
namespace arm {

	void grab() {
		RCServo0.write(0);
	}

	void release() {
		RCServo0.write(150);
	}

	void turn_arm(int angle) {
		

			
	}

	void extend_arm() {
		time = millis();
		while (digitalRead(PICKUP_SWITCH) && (millis()-time<PICKUP_DELAY)) {//TODO:add alternative if passenger not picked up
			motor.speed(ACTUATOR,ACTUATOR_SPEED);//actuator and have feedback
		}
		motor.stop(ACTUATOR);
		grab();


		//de_extend arm, move turntable towards bucket(TODO:Have feedback from turntable), place passenger in bucket
	}

	void pickup(int dir) {




	}


}