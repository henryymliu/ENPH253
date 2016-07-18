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
	extern const uint16_t* KP_SAVE_ADDRESS;
	extern const uint16_t* KD_SAVE_ADDRESS;
	extern uint8_t TF_KP;
	extern uint8_t TF_KD;
	
	void saveVal(uint16_t* address, uint8_t val);

}
#endif

