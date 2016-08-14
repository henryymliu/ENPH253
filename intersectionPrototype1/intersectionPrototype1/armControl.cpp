// 
// 
// 

#include "armControl.h"
#include "Arduino.h"
#include "phys253.h"
#include "navigation.h"
#include "tapeFollow.h"

#define PICKUP_SWITCH 0
#define ARM_SWITCH 1
#define ACTUATOR 1
#define ACTUATOR_SPEED -50
#define PICKUP_DELAY 3000
#define RETRACT_DELAY 3000
#define LEFT_ANGLE 15
#define RIGHT_ANGLE -15
#define UP_ANGLE 100
#define PLANE_ANGLE 15
#define TURN_DELAY 1000


unsigned long time;
namespace arm {

	motorEncoder turntable = motorEncoder(tt_ePR, tt_ePL);
	motorEncoder armActuator = motorEncoder(aa_ePR, aa_ePL);
	const int MOVEMENT_TIMEOUT = 2000;
	void grab() {
		RCServo1.write(90);   //claw attached to RCServo 1
	}

	void vert_move(int angle) { //vertical movement from RCServo 2
		RCServo2.write(angle);
	}

	void release() {
		RCServo1.write(150);
	}

	void turn_arm(int pos) {
		//-17 is right, 17 is left
		const int TT_SPEED = 50;
		unsigned long startTime = millis();

		int lastPos = arm::turntable.rotaryPosition;
		if (pos < arm::turntable.rotaryPosition) {
			while (pos < arm::turntable.rotaryPosition) {
				if (millis() - startTime > 1000) {
					if (abs(arm::turntable.rotaryPosition - lastPos) < 2) {
						break;
					}
					lastPos = arm::turntable.rotaryPosition;
					startTime = millis();
				}
				motor.speed(2, TT_SPEED);
				arm::turntable.readEncoderAngle();
			}
		}
		else {
			while (pos > arm::turntable.rotaryPosition) {
				if (millis() - startTime > 1000) {
					if (abs(arm::turntable.rotaryPosition - lastPos) < 2) {
						break; //motor is stuck, no point turning more
					}
					lastPos = arm::turntable.rotaryPosition;
					startTime = millis();		
				}
				motor.speed(2, -TT_SPEED);
				arm::turntable.readEncoderAngle();

			}
			
			//armActuator.
		}
		motor.stop(2);
	}
	void turn_actuator(int pos) {
		const int TT_SPEED = 60;
		unsigned long startTime = millis();

		int lastPos = arm::armActuator.rotaryPosition;
		if (pos < arm::armActuator.rotaryPosition) {
			while (pos < arm::armActuator.rotaryPosition) {
				if (millis() - startTime > 1000) {
					if (abs(arm::armActuator.rotaryPosition - lastPos) < 2) {
						break;
					}
					lastPos = arm::armActuator.rotaryPosition;
					startTime = millis();
				}
				motor.speed(1, -TT_SPEED);
				arm::armActuator.readEncoderAngle();
			}
		}
		else {
			while (pos > arm::armActuator.rotaryPosition) {
				if (millis() - startTime > 1000) {
					if (abs(arm::armActuator.rotaryPosition - lastPos) < 2) {
						break; //motor is stuck, no point turning more
					}
					lastPos = arm::armActuator.rotaryPosition;
					startTime = millis();
				}
				motor.speed(1, TT_SPEED);
				arm::armActuator.readEncoderAngle();

			}
			
			//armActuator.

		}
		motor.stop(1);
	}

	void extend() {

		time = millis();

		//digitalRead(PICKUP_SWITCH) &&
		while ((millis() - time<PICKUP_DELAY)) {//TODO:add alternative if passenger not picked up
			motor.speed(ACTUATOR, ACTUATOR_SPEED);//actuator and have feedback
												  //armActuator.readEncoderAngle();
		}
		motor.stop(ACTUATOR);


		//de_extend arm, move turntable towards bucket(TODO:Have feedback from turntable), place passenger in bucket
	}
	void extend_grab() {

		time = millis();
		
		//digitalRead(PICKUP_SWITCH) &&
		while ( (millis()-time<PICKUP_DELAY)) {//TODO:add alternative if passenger not picked up
			motor.speed(ACTUATOR,ACTUATOR_SPEED);//actuator and have feedback
			//armActuator.readEncoderAngle();
		}
		motor.stop(ACTUATOR);
		grab();


		//de_extend arm, move turntable towards bucket(TODO:Have feedback from turntable), place passenger in bucket
	}

	void retract() {
		time = millis();
		while ((millis() - time<RETRACT_DELAY)) {
			motor.speed(ACTUATOR, -ACTUATOR_SPEED);
			//armActuator.readEncoderAngle();
		}
		motor.stop(ACTUATOR);
	}

	void pickup(int dir) {//assumes robot is aligned
		
		//if (dir == LEFT) {
			//turn_arm(LEFT_ANGLE);
			//tapeFollow::turnLeft();
		//}
		//else
			//turn_arm(RIGHT_ANGLE);
		//turn_actuator(15);
		
		if (dir == RIGHT) {
			release(); //careful
			delay(500);
			vert_move(160);
			delay(500);
			extend_grab();
			delay(500);
			retract();
			delay(500);
		}
		else if(dir==LEFT) {
			tapeFollow::turnAround();
			motor.stop_all();
			delay(100);
			time = millis();
			while (millis() - time < TURN_DELAY || mux::readMUXIn(2,mux::NEAR_IR_RIGHT) < mux::NEAR_IR_THRESH){
				
				motor.speed(L_MOTOR, 20);
				motor.speed(R_MOTOR, 20);
				
			}
			motor.stop_all();
			release();
			//delay(400);
			delay(500);
			vert_move(160);
			delay(200);
			extend_grab();
			delay(500);
			retract();
			delay(500);
			tapeFollow::turnAround();
		}
		/*
		vert_move(TILTSERVO_STOW_ANGLE);
		turn_arm(0);
		retract();
		*/
		//stow();
		vert_move(120);
		//turn_actuator(15);
		//if (dir == LEFT) {
		//	tapeFollow::turnRight();
		//}
		
	}

	void stow() {
		vert_move(TILTSERVO_STOW_ANGLE);
		turn_arm(0);
		turn_actuator(0);
	}

	double motorEncoder::readEncoderAngle() {
		rightState = digitalRead(encoderPinR);
		leftState = digitalRead(encoderPinL);

		//changing states
		if (state == 0) {
			if (leftState == 1 && rightState == 0)
				state++;
			if (leftState == 0 && rightState == 1)
				state--;
		}

		else if (state == 1) {
			if (leftState == 1 && rightState == 1)
				state++;
			if (leftState == 0 && rightState == 0)
				state--;
		}

		else if (state == 2) {
			if (leftState == 0 && rightState == 1)
				state++;
			if (leftState == 1 && rightState == 0)
				state--;
		}

		else if (state == 3) {
			if (leftState == 0 && rightState == 0)
				state++;
			if (leftState == 1 && rightState == 1)
				state--;
		}

		else if (state == -1) {
			if (leftState == 0 && rightState == 0)
				state++;
			if (leftState == 1 && rightState == 1)
				state--;
		}

		else if (state == -2) {
			if (leftState == 0 && rightState == 1)
				state++;
			if (leftState == 1 && rightState == 0)
				state--;
		}

		else if (state == -3) {
			if (leftState == 1 && rightState == 1)
				state++;
			if (leftState == 0 && rightState == 0)
				state--;
		}

		else if (state == 4) {
			rotaryPosition++;
			state = 0;
		}

		else if (state == -4) {
			rotaryPosition--;
			state = 0;
		}

		return rotaryPosition;
	}

	double turntableAngle(motorEncoder tt) {
		return tt.rotaryPosition * 90.0 / 11.0;
	}

}