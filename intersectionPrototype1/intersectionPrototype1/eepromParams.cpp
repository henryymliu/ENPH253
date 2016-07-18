// 
// 
// 

#include "eepromParams.h"

namespace eepromParams {
	uint8_t TF_KP = 6;
	uint8_t TF_KD = 22;
	const uint16_t* KP_SAVE_ADDRESS = (uint16_t*) 0;
	const uint16_t* KD_SAVE_ADDRESS = (uint16_t*) 2;

	void saveVal(uint16_t* address, uint8_t val) {
		eeprom_write_word(address, val);
	}
}
