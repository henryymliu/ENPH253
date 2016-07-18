// menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <avr\eeprom.h>
#include "eepromParams.h"

namespace Menu {

	enum MainMenuItems {TFParam ,Strategy, Tests, Competition};

	enum TestMenuItems {TapeFollow, NavTest, ArmTest,IRTest};

	enum TFParamMenuItems {kdParams,thresholds};
	enum tfVars { spParam, dParam, pParam };
	
	extern MainMenuItems currMenu;

	void menuLoop();
	void strategyMenuLoop();
	void tapeFollowMenuLoop(TFParamMenuItems tfp);
	void testsMenuLoop();


};

#endif

