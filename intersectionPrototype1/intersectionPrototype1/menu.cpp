// 
// 
// 

#include "menu.h"
#include "eepromParams.h"
#include <phys253.h>
#define DISP_REFRESH_RATE 30


void Menu::switchMenu(Menu::MainMenuItems menu){
	switch (menu){
	case TFParam:
		LCD.clear(); LCD.home();
		LCD.setCursor(0, 1);
		LCD.print("Kp:"); LCD.print("eee");
		break;

	

	}

}

