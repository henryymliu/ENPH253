// 
// 
// 

#include "eepromParams.h"

namespace eepromParams {
	uint8_t TF_KP = 6;
	uint8_t TF_KD = 22;
	uint16_t* eepromAddress;

	void saveKP(int kp) {
		eeprom_write_word(eepromAddress, kp);
	}

	void saveKD(int kd) {

	}
}
