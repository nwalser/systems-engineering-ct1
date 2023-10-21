#include <stdlib.h>
#include <reg_ctboard.h>
#include <math.h>

/* User includes */
#include "utils_ctboard.h"


#define DIP_0_7 0x60000200
#define LED_0_7 0x60000100

#define HEX_SWITCH 0x60000211
#define DS0 0x60000110


static const uint8_t seven_segment_lut[16] = {
	0b11000000, // 0
	0b11111001,
	0b10100100,
	0b10110000,
	0b10011001,
	0b10010010,
	0b10000010,
	0b11111000,
	0b10000000,
	0b10010000, // 9
	0b10001000, // a
	0b10000011,
	0b11000110,
	0b10100001,
	0b10000110,
	0b10001110, // f
};

int main(void)
{	
	while(1){
		uint32_t io = read_word(DIP_0_7);
		write_word(LED_0_7, io);
		
		uint8_t current = read_byte(HEX_SWITCH);
		write_byte(DS0, seven_segment_lut[current & 0x0F]);
	}
}
