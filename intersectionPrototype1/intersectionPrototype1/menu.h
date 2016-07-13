// menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <avr\eeprom.h>

class Menu {
public:
	enum MainMenuItems {TFParam ,Strategy, Tests, Competition};

	enum TestMenuItems {TapeFollow, NavTest, ArmTest,IRTest};
	enum TFParamMenuItems {DispK, SaveK, LoadK};
	
	MainMenuItems currMenu = TFParam;

	void switchMenu(MainMenuItems menu);

};

#endif

