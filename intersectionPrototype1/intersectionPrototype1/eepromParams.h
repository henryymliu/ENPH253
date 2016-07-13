// eepromParams.h

#ifndef _EEPROMPARAMS_h
#define _EEPROMPARAMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <avr/eeprom.h>


namespace eepromParams {
	extern uint16_t* eepromAddress;
	extern uint8_t TF_KP;
	extern uint8_t TF_KD;
	
	void saveKP(int kp);
	void saveKD(int kd);

}
#endif

