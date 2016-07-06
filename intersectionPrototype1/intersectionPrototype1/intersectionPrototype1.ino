/*
 Name:		intersectionPrototype1.ino
 Created:	6/29/2016 6:51:41 PM
 Author:	Henry
*/

//NOTE: ADD HEADERS HERE
#include <tapeFollow.h>
#include <ServoTINAH.h>
#include <phys253pins.h>
#include <motor.h>
#include <phys253.h>          
#include <LiquidCrystal.h> 
void setup() {

#include <phys253setup.txt>
	Serial.begin(9600);

}

TapeFollow tf;

void loop() {
	tf.tapeFollow();
}
