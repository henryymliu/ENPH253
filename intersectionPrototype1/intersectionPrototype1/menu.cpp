// 
// 
// 

#include "menu.h"
#include "eepromParams.h"
#include <phys253.h>
#define DISP_REFRESH_RATE 50

namespace Menu {
	MainMenuItems currMenu = TFParam;
	int selectedCursorLoc_R = 1;
	int selectedCursorLoc_C = 0;


	tfVars activeVar = spParam;
	int displayTimer = 0;
	void menuLoop() {

		switch (currMenu) {
		case TFParam:

			tapeFollowMenuLoop(kdParams);
			break;

		case Strategy:
			break;

		case Tests:
			break;

		case Competition:
			break;

		}


	}
	void strategyMenuLoop() {

	}

	void testsMenuLoop() {

	}

	void tapeFollowMenuLoop(TFParamMenuItems tfp) {
		switch (tfp) {
		case kdParams:
			if (displayTimer > DISP_REFRESH_RATE) {
				LCD.clear(); LCD.setCursor(1, 0);
				LCD.print("TFSp:");
				LCD.setCursor(selectedCursorLoc_C, selectedCursorLoc_R); LCD.print(">");
				LCD.setCursor(1, 1);
				LCD.print("kp:"); LCD.print(eepromParams::TF_KP);
				LCD.setCursor(7, 1);
				LCD.print("kd:"); LCD.print(eepromParams::TF_KD);
				displayTimer = 0;
			}
			else {
				displayTimer++;
			}
		case thresholds:
			break;


		}
		/********button handling cases*********/

		//save variable
		if (startbutton()) {
			delay(500);
			if (startbutton()) {

			}
		}

		//switch active variable
		if (startbutton()) {
			delay(75);
			if (startbutton()) {
				if (1 + (int)activeVar > (int)pParam) { //shitty hack
					activeVar = (tfVars)(0);
				}
				else {
					activeVar = (tfVars)(1 + (int)activeVar);
				}

			}




		}

	}
}

