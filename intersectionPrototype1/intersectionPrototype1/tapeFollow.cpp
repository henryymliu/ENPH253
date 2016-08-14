
#include <phys253.h>          
#include <LiquidCrystal.h> 
#include "tapeFollow.h"
#include "eepromParams.h"

namespace tapeFollow{

//int error = 0;
	int bumper_switch1 = 5;
	int bumper_switch2 = 4;
	bool intersectionDetected = false;
	bool collision = false;
	bool dropoff = false;
	int error;
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
	int q = 1;

	int intersectLeft;
	int intersectRight;
	unsigned long currTime = millis();

		//same tape following algo as in lab 5
	void followTape(int motorSpeed) {

		//kp = map(knob(KP_KNOB), 0, 1023, 0, 99);
		//kd = map(knob(KD_KNOB), 0, 1023, 0, 99);
		kp = eepromParams::TF_KP;
		kd = eepromParams::TF_KD;
		thresh = eepromParams::TF_thresh;
		//int tlthresh = 40;
		left = analogRead(TD_L);
		right = analogRead(TD_R);

		//on tape
		if ((left >= thresh) && (right >= thresh))
			error = 0;
		//slightly to the right
		if ((left >=thresh) && (right < thresh))
			error = -1;

		//slightly to the left
		if ((left < thresh) && (right >= thresh))
			error = 1;

		//welp, we're way off
		if ((left < thresh) && (right < thresh)) {
			if (lerr > 0) error = 3; //left
			if (lerr < 0) error = -3; //right
		}

		//interrupt function if intersection detected, maybe trigger ISR in the future
		

		//for now turn, based on first intersection branch detected
		//delay to ensure robot is successfully tape following before detecting another intersection to prevent
		//false positives

		//currTime = millis();
		if ((millis() - currTime) > INTERSECTION_TURNING_DEADZONE) {
			intersectLeft = analogRead(ID_L);
			intersectRight = analogRead(ID_R);

			if (intersectLeft >= thresh) {
				delay(10);
				intersectLeft = analogRead(ID_L);
				if (intersectLeft >= thresh) {
					intersectionDetected = true;
					currTime = millis();
					//turnLeft();
				}
			}
			else if (intersectRight >= thresh) {
				delay(10);
				intersectRight = analogRead(ID_R);
				if (intersectRight >= thresh) {
					intersectionDetected = true;
					currTime = millis();
					//turnRight();
				}
			}
			
		}
		
		if (error != lerr) {
			recerr = lerr;
			q = m;
			//d = kd*(((double)error - (double)recerr) / ((double)m));
			m = 1;
		}

		p = kp*error;
		d = 10*kd*(((double)error - (double)recerr) / ((double)q + (double)m));
		cons = p + d;
		//Serial.print("cons: "); Serial.print(cons);
		//Serial.print("err: "); Serial.print(error + "\n");

		//temp print to screen stuff for debugging; in actual implementation abstract
		//these values into getter functions, and print only in menu

		/*
		if (c >= 30) {
			LCD.clear();LCD.home();
			LCD.print("R:");
			LCD.print(right);

			LCD.setCursor(5, 0);
			LCD.print("L:");
			LCD.print(left);

			LCD.setCursor(10, 0);
			LCD.print("I:");
			LCD.print(intersectRight);

			LCD.setCursor(0, 1);
			LCD.print("J:");
			LCD.print(intersectLeft);

			LCD.setCursor(5, 1);

			
			LCD.print("p:");
			LCD.print((int)kp);

			LCD.setCursor(10, 1);
			LCD.print("d:");
			LCD.print((int)kd);
			
			c = 0;
		}

		c++;
		*/
	    m++;
		lerr = error;
		motor.speed(L_MOTOR, motorSpeed + cons);
		motor.speed(R_MOTOR, motorSpeed - cons);

		//look for collision on bumper
		if (!digitalRead(bumper_switch1) || !digitalRead(bumper_switch2)) {
			//motor.stop_all();
			delay(100);
			if (!digitalRead(bumper_switch1) || !digitalRead(bumper_switch2)) {
				collision = true;
			}
		}
	}

	
		//future consideration: make angle a parameter to optimize turning, maybe power too

		//for turning, turn left/right until tape detectors redetect tape
		void turnLeft() {
			//LCD.clear();LCD.home();
			LCD.setCursor(0, 1);
			LCD.print("TURN L");
			motor.speed(L_MOTOR, -55);
			motor.speed(R_MOTOR, 55);
			delay(INTERSECTION_TURNING_DELAY_MILLI);
			right = analogRead(TD_R);
			while (right < thresh) {
				right = analogRead(TD_R);
			}
			error = 0;
			currTime = millis();
		}
		void turnRight() {
			LCD.setCursor(0, 1);
			LCD.print("TURN R");
			motor.speed(L_MOTOR, 55);
			motor.speed(R_MOTOR, -55);
			delay(INTERSECTION_TURNING_DELAY_MILLI);
			left = analogRead(TD_L);
			while (left < thresh) {
				left = analogRead(TD_L);
			}
			error = 0;
			currTime = millis();
		}

		void turnAround() {
			bool wiggle = false;
			LCD.setCursor(0, 1);
			motor.stop(L_MOTOR);
			motor.stop(R_MOTOR);
			LCD.print("TURN A");
			unsigned long time = millis();
			while (millis() - time < 500) {
				motor.speed(L_MOTOR,-50);
				motor.speed(R_MOTOR, -50);
			}
			motor.speed(L_MOTOR, 60);
			motor.speed(R_MOTOR, -60);
			delay(INTERSECTION_TURNING_DELAY_MILLI + 900);
			left = analogRead(TD_L);
			while (left < thresh) {
				left = analogRead(TD_L);
				if (millis() - time > 4000) {

					motor.speed(L_MOTOR, 50);
					motor.speed(R_MOTOR, 50);
					delay(300);
					motor.speed(L_MOTOR, 60);
					motor.speed(R_MOTOR, -60);
					time = millis();
				}
			}
			error = 0;
			currTime = millis();


		}

	}