#include <OSFS.h>
#include <EEPROM.h>

////////////////////////////////////////////////////////////////////////////////
// START OF DECLARATIONS FOR OSFS                                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * The following declarations tell OSFS how to access your storage medium and
 * how much if it it's allowed to manage. For an Arduino, the following
 * definitions will allow you to write to all 1024 bytes of its internal EEPROM.
 * Allowing the user to define these functions means that this library is
 * generalised for any type of storage medium including external SPI devices for
 * example.
 */

uint16_t OSFS::startOfEEPROM = 1;
uint16_t OSFS::endOfEEPROM = 1024;

void OSFS::readNBytes(uint16_t address, unsigned int num, byte* output) {
	for (uint16_t i = address; i < address + num; i++) {
		*output = EEPROM.read(i);
		output++;
	}
}
void OSFS::writeNBytes(uint16_t address, unsigned int num, const byte* input) {
	for (uint16_t i = address; i < address + num; i++) {
		EEPROM.update(i, *input);
		input++;
	}
}

// Useful consts
const OSFS::result noerr = OSFS::result::NO_ERROR;
const OSFS::result notfound = OSFS::result::FILE_NOT_FOUND;