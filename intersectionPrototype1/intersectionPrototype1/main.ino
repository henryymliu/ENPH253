

/*
 Name:		intersectionPrototype1.ino
 Created:	6/29/2016 6:51:41 PM
 Author:	Henry
*/

//NOTE: ADD HEADERS HERE

#include "IR.h"
#include "eepromParams.h"
#include "navigation.h"
#include "menu.h"
#include <phys253.h>          
#include <LiquidCrystal.h> 
#include "tapeFollow.h"


void setup() {

	#include <phys253setup.txt>
	Serial.begin(9600);

}

//tapeFollow tf;
void loop() {
	tapeFollow::followTape(70);
	
}

