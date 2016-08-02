// 
// 
// 

#include "menu.h"
#include "eepromParams.h"
#include "tapeFollow.h"
#include <phys253.h>
#define DISP_REFRESH_RATE 60

namespace menu{
	//SHORTSTOPBUTTON RESERVED FOR MENU CHANGES 
	menuStates currMenu = PIDParams;
	buttonPressStates lastButtonState = none;
	bool canModifyValues = false;

	int dispTime = 0;
	PIDParamsMenu pid;
	void menuLoop(){
		
		if (dispTime > DISP_REFRESH_RATE){
			lastButtonState = detectButtonPress();
			if (lastButtonState == buttonPressStates::shortStopButton){
				switchMenu();
				canModifyValues = false;
				lastButtonState = none;
			}

			switch (currMenu){
			case Competition:
				break;

			case PIDParams:
				pid.paramsDisplayLoop();

				switch (lastButtonState){
				case longStopButton:
					LCD.clear(); LCD.home();
					LCD.print("EEPROM PID");
					LCD.setCursor(0, 1); 
					LCD.print("values loaded");
					delay(1000);
					canModifyValues = false;
					eepromParams::TF_KD = eepromParams::readVal(eepromParams::KD_SAVE_ADDRESS);
					eepromParams::TF_KP = eepromParams::readVal(eepromParams::KP_SAVE_ADDRESS);
					lastButtonState = none;
					break;

				case shortStartButton:
					
					canModifyValues = true;
					break;

				case longStartButton:
					canModifyValues = false;
					eepromParams::saveVal(eepromParams::KD_SAVE_ADDRESS, eepromParams::TF_KD);
					eepromParams::saveVal(eepromParams::KP_SAVE_ADDRESS, eepromParams::TF_KP);
					LCD.clear(); LCD.home();
					LCD.print("Saved to EEPROM");
					delay(1000);

					lastButtonState = none;
					break;

				}



				break;

			case tapeFollowThreshold:
				LCD.clear(); LCD.home();
				LCD.print("R");
				LCD.print(analogRead(TD_R));

				LCD.setCursor(5, 0);
				LCD.print("L");
				LCD.print(analogRead(TD_L));

				LCD.setCursor(10, 0);
				LCD.print("IR");
				LCD.print(analogRead(ID_R));

				LCD.setCursor(0, 1);
				LCD.print("IL");
				LCD.print(analogRead(ID_L));

				LCD.setCursor(7, 1);
				LCD.print("T");
				LCD.print((int)eepromParams::TF_thresh);
				if (canModifyValues){
					eepromParams::TF_thresh = knob(6);
					LCD.setCursor(13, 1);
					LCD.print("**");
				}

				switch (lastButtonState){
				case shortStartButton:

					canModifyValues = true;
					break;

				case longStopButton:
					LCD.clear(); LCD.home();
					LCD.print("EEPROM Thresh");
					LCD.setCursor(0, 1);
					LCD.print("value loaded");
					delay(1000);
					canModifyValues = false;
					eepromParams::TF_thresh = eepromParams::readVal(eepromParams::THRESH_SAVE_ADDRESS);
					lastButtonState = none;
					break;

				case longStartButton:
					canModifyValues = false;
					eepromParams::saveVal(eepromParams::THRESH_SAVE_ADDRESS,eepromParams::TF_thresh);
					LCD.clear(); LCD.home();
					LCD.print("Saved to EEPROM");
					delay(1000);
					lastButtonState = none;
					break;
				}

				break;

			case tapeFollowTest:
				LCD.clear(); LCD.home();
				LCD.print("Hold START to");
				LCD.setCursor(0, 1);
				LCD.print("begin TF");
				if (lastButtonState == longStartButton){
					while (!stopbutton){
						tapeFollow::followTape(70); //change to vary speed later
					}
				}
				break;
			case navigationTest:
				break;

			case IRTest:
				break;

			case armCalibTest:
				break;
				
			}
			dispTime = 0;
		}
		dispTime++;
	}

	void switchMenu(){
		switch (currMenu){
		case Competition:
			break;

		case PIDParams:
			currMenu = tapeFollowThreshold;
			break;

		case tapeFollowThreshold:
			currMenu = tapeFollowTest;
			break;

		case tapeFollowTest:
			currMenu = PIDParams;
			break;

		case navigationTest:
			break;

		case IRTest:
			break;

		case armCalibTest:
			break;

		}
	}

	buttonPressStates detectButtonPress(){
		buttonPressStates bps = none;
		unsigned long buttonTime = millis();
		if (startbutton()){
			/*
			delay(200); //brief press
			if (startbutton()){
				bps = shortStartButton;
			}
			delay(1000); //long press
			if (startbutton()){
				bps = longStartButton;
			}
			*/
			while (startbutton()){

			}
			if (millis() - buttonTime > 800){
				bps = longStartButton;
			}
			else if (millis() - buttonTime > 100){
				bps = shortStartButton;
			}
		}

		else if (stopbutton()){
			while (stopbutton()){

			}
			if (millis() - buttonTime > 800){
				bps = longStopButton;
			}
			else if (millis() - buttonTime > 100){
				bps = shortStopButton;
			}
		}

		return bps;
	}

	void PIDParamsMenu::paramsDisplayLoop(){
		LCD.clear(); LCD.home();
		LCD.print("PID Params");

		LCD.setCursor(0, 1);
		LCD.print("kp:");
		LCD.print((int) eepromParams::TF_KP);

		LCD.setCursor(6, 1);
		LCD.print("d:");
		LCD.print((int) eepromParams::TF_KD);

		if (canModifyValues){
			LCD.setCursor(14, 0);
			LCD.print("**");
			eepromParams::TF_KP = map(knob(6), 0, 1023, 0, 99);
			eepromParams::TF_KD = map(knob(7), 0, 1023, 0, 99);
		}
	}
	

}