
#include <phys253.h>          
#include <LiquidCrystal.h> 
#include "tapeFollow.h"

namespace tapeFollow {
	int motorSpeed = 500;

	double kp;
	double kd;
	double gain;
	int thresh;

	int left;
	int right;

	int error;
	int lerr = 0;
	int recerr = 0;
	int c = 0;

	double p;
	double d;
	double cons;
	int m = 1;
	int q;

	//same tape following algo as in lab 5
	void followTape() {

		kp = knob(6);
		kd = knob(7);
		gain = 20;
		thresh = 30;

		left = analogRead(0);
		right = analogRead(3);

		if ((left >= thresh) && (right >= thresh))
			error = 0;
		if ((left >= thresh) && (right < thresh))
			error = -1;
		if ((left < thresh) && (right >= thresh))
			error = 1;
		if ((left < thresh) && (right < thresh)) {
			if (lerr > 0) error = 5;
			if (lerr < 0) error = -5;
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
			LCD.print("T:");
			LCD.print(thresh);

			LCD.setCursor(0, 1);
			LCD.print("Kp:");
			LCD.print((int)kp);

			LCD.setCursor(8, 1);
			LCD.print("Kd:");
			LCD.print((int)kd);

			c = 0;
		}

		c++;
		motor.speed(0, motorSpeed + cons);
		motor.speed(3, motorSpeed - cons);
	}

}
