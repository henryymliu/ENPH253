// 
// 
// 

#include "menu.h"
#include "eepromParams.h"
#include "tapeFollow.h"
#include "armControl.h"
#include "path.h"
#include "navigation.h"
#include <phys253.h>
#define DISP_REFRESH_RATE 60

namespace menu{
	//SHORTSTOPBUTTON RESERVED FOR MENU CHANGES 
	menuStates currMenu = PIDParams;
	buttonPressStates lastButtonState = none;
	bool canModifyValues = false;

	const courseGraph::node* next_node;
	const courseGraph::node* currN;
	const courseGraph::node* prevN1;

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
					LCD.clear(); LCD.home();
					LCD.print("Press STOP to");
					LCD.setCursor(0, 1);
					LCD.print("stop TF");
					while (!stopbutton()){
						tapeFollow::followTape(80); //change to vary speed later
					}
					motor.stop_all();
					lastButtonState = none;
				}
				break;
			case navigationTest: {
				//const courseGraph::node* next_node;
				LCD.clear();LCD.home();
				LCD.print("cN:");
				currN =nav::graph.nodeArray[(int)map(knob(6), 5, 1015, 0, 19)];
				LCD.print(currN->ID);

				LCD.setCursor(4, 0);
				LCD.print("pN1:");
				prevN1 = currN->neighbors[(int)map(knob(7), 5, 1000, 0, 3)];
				LCD.print(prevN1->ID);
				const courseGraph::node* prevN2 = prevN1->neighbors[0];

				switch (lastButtonState) {
				case longStartButton: {
					while (!stopbutton()) {
						
						LCD.clear();LCD.home();
						/*

						LCD.print("IR ");
						switch (nav::dir) {
						case 0:
							LCD.print("L");
							break;
						case 1:
							LCD.print("F");
							break;
						case -1:
							LCD.print("B");
							break;
						case 2:
							LCD.print("R");
							break;
						case -2:
							LCD.print("N");
							break;
						}
						*/
						//implement dropoff flag later
						int passengerDir = nav::checkAdjacentPassengers();
						
						//LCD.setCursor(7, 0);
						switch (passengerDir) {
						case LEFT:
							nav::dropoff(prevN1, currN);
							break;
						case RIGHT:
							nav::dropoff(prevN1, currN);
							break;

						}
						/*
						//switch (passengerDir) {
						//case LEFT:
							//tapeFollow::turnAround();
							//unsigned int t = millis();
							//while (millis() - t < 1500) {
							//	motor.speed(LEFTMOTOR)
							//}
							//arm::pickup(LEFT);
							//LCD.print("PL");
							//nav::dropoff(prevN1, currN);
							break;
						case RIGHT:
							motor.stop(L_MOTOR);
							motor.stop(R_MOTOR);
							arm::pickup(RIGHT);
							//LCD.print("PR");
							delay(1000);
							nav::dropoff(prevN1, currN);
							motor.stop_all();
							LCD.print("k chill");
							break;
							
						}
						*/
						LCD.setCursor(11, 0);
						LCD.print("CN:"); LCD.print(currN->ID);
						LCD.setCursor(0, 1);
						//turn functions printed here

						tapeFollow::followTape(75);
						if (tapeFollow::intersectionDetected) {
							tapeFollow::followTape(5);
							
							next_node = nav::turn(currN, prevN1, prevN2);
							LCD.setCursor(8, 1);
							LCD.print("Inter");
							prevN1 = currN;
							prevN2 = prevN1;
							currN = next_node;
							tapeFollow::intersectionDetected = false;
						}

						

						if (tapeFollow::collision) {
							tapeFollow::turnAround();
							currN = prevN1;
							prevN1 = next_node;
							tapeFollow::collision = false;
							 
						}
						//tapeFollow::intersectionDetected = false;
						//tapeFollow::collision = false;
					}
					motor.stop_all();
					lastButtonState = none;
					break;
				}

				}
				break;
			}
			case IRTest:
				LCD.clear();LCD.home();
				LCD.print(mux::readMUXIn(2,mux::NEAR_IR_LEFT));
				LCD.setCursor(6, 0);
				LCD.print(mux::readMUXIn(2,mux::NEAR_IR_RIGHT));

				
				LCD.setCursor(0, 1);
				LCD.print("T:");
				LCD.print(mux::NEAR_IR_THRESH);

				switch (lastButtonState) {
				case shortStartButton:
					mux::NEAR_IR_THRESH = knob(6);
					break;
				}
				break;

			case armCalibTest:
				LCD.clear();LCD.home();
				LCD.print("TT:");
				LCD.print(arm::turntable.rotaryPosition);
				arm::turntable.readEncoderAngle();
				LCD.setCursor(8, 0);
				LCD.print("AP:");
				arm::armActuator.readEncoderAngle();
				LCD.print(arm::armActuator.rotaryPosition);
				LCD.setCursor(0, 1);
				int tiltPos = map(knob(6), 0, 1023, 0, 180);
				LCD.print("TA:"); LCD.print(tiltPos);
				//RCServo2.write(tiltPos);

				LCD.setCursor(6, 1);
				int turnPos = map(knob(7), 0, 1023, -15, 15);
				LCD.print("TuA:"); LCD.print(turnPos);
				
				//arm::turn_arm(turnPos);
				
				switch (lastButtonState) {
				case longStartButton:
					arm::armActuator.rotaryPosition = 0;
					arm::turntable.rotaryPosition = 0;
					break;
				}
				break;
				
			}
			dispTime = 0;
		}
		dispTime++;
	}

	//Determines menu order upon SHORTSTOPBUTTON
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
			currMenu = navigationTest;
			break;

		case navigationTest:
			currMenu = IRTest;
			break;

		case IRTest:
			currMenu = armCalibTest;
			break;

		case armCalibTest:
			currMenu = PIDParams;
			break;

		}
	}

	buttonPressStates detectButtonPress(){
		buttonPressStates bps = none;
		unsigned long buttonTime = millis();
		if (startbutton()){

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