// 
// 
// 

#include "eepromParams.h"

namespace eepromParams {
	uint8_t TF_KP = 8;
	uint8_t TF_KD = 30;
	uint16_t TF_thresh = 150;
	uint8_t TURNTABLE_angle = 0;
	uint8_t ACTUATOR_pos = 0;


	uint16_t* KP_SAVE_ADDRESS = (uint16_t*) 0;
	uint16_t* KD_SAVE_ADDRESS = (uint16_t*) 2;
	uint16_t *THRESH_SAVE_ADDRESS	 = (uint16_t*)4;
	uint16_t* TURNTABLE_SAVE_ADDRESS = (uint16_t*)6;
	uint16_t* ACTUATOR_SAVE_ADDRESS = (uint16_t*)8;

	//recall that uint16_t is 16 bits, therefore 2 bytes
	void saveVal(uint16_t* address, uint8_t val) {
		eeprom_write_word(address, val);
	}

	 uint16_t readVal(uint16_t *address){
		return eeprom_read_word(address);
	}
}
