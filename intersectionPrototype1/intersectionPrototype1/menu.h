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

namespace menu{
	enum menuStates{ Competition, PIDParams, tapeFollowThreshold, tapeFollowTest, navigationTest, IRTest, armCalibTest };
	enum buttonPressStates{none, shortStartButton, longStartButton, shortStopButton, longStopButton};

	enum state{ inMenu, TapeFollow  };

	void menuLoop();
	void switchMenu();

	buttonPressStates detectButtonPress();
	extern buttonPressStates lastButtonState;
	void competitionMenuLoop();

	struct PIDParamsMenu{
		
		enum pidMenuState{display,modify};
		void paramsDisplayLoop();
		void confirmSaveValLoop();

	};
	void PIDParamsMenuLoop();
	void tapeFollowThresholdMenuLoop();
	void tapeFollowTestMenuLoop();
	void navigationTestMenuLoop();
	void IRTestMenuLoop();
}


#endif

