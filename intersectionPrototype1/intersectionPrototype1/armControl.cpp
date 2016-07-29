// 
// 
// 

#include "armControl.h"
#include "Arduino.h"
#include "phys253.h"

#define PICKUP_SWITCH 0
#define ARM_SWITCH 1
#define ACTUATOR 0
#define ACTUATOR_SPEED 50
#define PICKUP_DELAY 3000
#define RETRACT_DELAY 3500
#define LEFT_ANGLE 0
#define RIGHT_ANGLE 180
#define UP_ANGLE 100
#define PLANE_ANGLE 15


int time;
namespace arm {
	
	void grab() {
		RCServo0.write(0);   //claw attached to RCServo 0
	}

	void vert_move(int angle) { //vertical movement from RCServo 1
		RCServo1.write(angle);
	}

	void release() {
		RCServo0.write(150);
	}

	void turn_arm(int angle) {
		

			
	}

	void extend_grab() {

		time = millis();
		
		
		while (digitalRead(PICKUP_SWITCH) && (millis()-time<PICKUP_DELAY)) {//TODO:add alternative if passenger not picked up
			motor.speed(ACTUATOR,ACTUATOR_SPEED);//actuator and have feedback
		}
		motor.stop(ACTUATOR);
		grab();


		//de_extend arm, move turntable towards bucket(TODO:Have feedback from turntable), place passenger in bucket
	}

	void retract() {
		time = millis();
		while (digitalRead(ARM_SWITCH) && (millis() - time<RETRACT_DELAY)) {
			motor.speed(ACTUATOR, -ACTUATOR_SPEED);
		}
		motor.stop(ACTUATOR);
	}

	void pickup(int dir) {//assumes robot is aligned
		vert_move(PLANE_ANGLE);
		//turn_arm(dir) TODO
		extend_grab();
		retract();
		vert_move(UP_ANGLE);





	}


}