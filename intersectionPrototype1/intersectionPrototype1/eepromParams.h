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
	extern uint16_t* KP_SAVE_ADDRESS;
	extern uint16_t* KD_SAVE_ADDRESS;
	extern uint16_t *THRESH_SAVE_ADDRESS;
	extern uint8_t TF_KP;
	extern uint8_t TF_KD;
	extern uint16_t TF_thresh;

	void saveVal(uint16_t* address, uint8_t val);
	uint16_t readVal(uint16_t* address);
}
#endif

