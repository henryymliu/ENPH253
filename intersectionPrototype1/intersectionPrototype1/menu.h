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
#include "path.h"

namespace menu{
	enum menuStates{ Competition, PIDParams, tapeFollowThreshold, tapeFollowTest, navigationTest, IRTest, armCalibTest };
	enum buttonPressStates{none, shortStartButton, longStartButton, shortStopButton, longStopButton};

	enum state{ inMenu, TapeFollow  };

	void menuLoop();
	void switchMenu();

	buttonPressStates detectButtonPress();
	extern buttonPressStates lastButtonState;
	void competitionMenuLoop();

	extern const courseGraph::node* next_node;
	extern const courseGraph::node* currN;
	extern const courseGraph::node* prevN1;

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

