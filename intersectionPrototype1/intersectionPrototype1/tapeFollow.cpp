// 
// 
// 

#include "tapeFollow.h"
#include <ServoTINAH.h>
#include <phys253pins.h>
#include <motor.h>
#include <phys253.h>          
#include <LiquidCrystal.h> 

//default constructor
TapeFollow::TapeFollow() {

}

//default destructor (not needed)
TapeFollow::~TapeFollow() {}

//same tape following algo as in lab 5
TapeFollow::tapeFollow() {

		kp = knob(6);
		kd = knob(7);
		gain = 20;
		thresh = 30;

		left = analogRead(0);
		right = analogRead(3);

		if ((left >= thresh) && (right >= thresh))
			error = 0;
		if ((left >= thresh) && (right<thresh))
			error = -1;
		if ((left<thresh) && (right >= thresh))
			error = 1;
		if ((left<thresh) && (right<thresh)) {
			if (lerr>0) error = 5;
			if (lerr<0) error = -5;
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


