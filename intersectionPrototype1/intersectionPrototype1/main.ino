

/*
 Name:		intersectionPrototype1.ino
 Created:	6/29/2016 6:51:41 PM
 Author:	Henry
*/

//NOTE: ADD HEADERS HERE

#include "multiplex.h"
#include "armControl.h"
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
enum state{inMenu, TapeFollow};

state currState = inMenu;
void loop() {
	/*
	switch (currState) {
	case inMenu:
		Menu::menuLoop();
		break;
	}
	*/
	//tapeFollow::followTape(70);

	LCD.clear(); LCD.home();
	LCD.print(mux::cycleReadIR());
	delay(30);
}

