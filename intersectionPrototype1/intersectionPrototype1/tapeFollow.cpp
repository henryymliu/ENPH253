
#include <phys253.h>          
#include <LiquidCrystal.h> 
#include "tapeFollow.h"



	//same tape following algo as in lab 5
	void tapeFollow::followTape(int motorSpeed) {

		kp = knob(KP_KNOB);
		kd = knob(KD_KNOB);
		gain = 20;
		thresh = 30;

		left = analogRead(TD_L);
		right = analogRead(TD_R);

		//on tape
		if ((left >= thresh) && (right >= thresh))
			error = 0;
		//slightly to the right
		if ((left >= thresh) && (right < thresh))
			error = -1;

		//slightly to the left
		if ((left < thresh) && (right >= thresh))
			error = 1;

		//welp, we're way off
		if ((left < thresh) && (right < thresh)) {
			if (lerr > 0) error = 5; //left
			if (lerr < 0) error = -5; //right
		}

		//interrupt function if intersection detected, maybe trigger ISR in the future
		intersectLeft = analogRead(ID_L);
		intersectRight = analogRead(ID_R);

		//for now turn, based on first intersection branch detected
		//delay to ensure robot is successfully tape following before detecting another intersection to prevent
		//false positives
		if ((millis() - currTime) > INTERSECTION_TURNING_DEADZONE) {
			if (intersectLeft >= thresh) {
				turnLeft();
			}
			else if (intersectRight >= thresh) {
				turnRight();
			}
		}

		if (error != lerr) {
			recerr = lerr;
			q = m;
			m = 1;
		}

		p = kp*error;
		d = kd*((double)error - (double)recerr) / ((double)q + (double)m);
		cons = p + d;
		Serial.print("cons: "); Serial.print(cons);
		Serial.print("err: "); Serial.print(error + "\n");

		//temp print to screen stuff for debugging; in actual implementation abstract
		//these values into getter functions, and print only in menu
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

		motor.speed(L_MOTOR, motorSpeed + cons);
		motor.speed(R_MOTOR, motorSpeed - cons);
	}


	//future consideration: make angle a parameter to optimize turning

	//for turning, turn left/right a little bit and then set error to be completely left/right off tape
	//NOTE: CONSIDER ROTATING UNTIL TAPE DETECTORS REDETECT TAPE (while loop)
	void tapeFollow::turnLeft() {
		motor.speed(L_MOTOR, -80);
		motor.speed(R_MOTOR, 80);
		delay(INTERSECTION_TURNING_DELAY_MILLI);
		right = analogRead(TD_R);
		while (right < thresh) {
			right = analogRead(TD_R);
		}
		error = 0;
		currTime = millis();
	}
	void tapeFollow::turnRight() {
		motor.speed(L_MOTOR, 80);
		motor.speed(R_MOTOR, -80);
		delay(INTERSECTION_TURNING_DELAY_MILLI);
		left = analogRead(TD_L);
		while (left < thresh) {
			left = analogRead(TD_L);
		}
		error = 0;
		currTime = millis();
	}