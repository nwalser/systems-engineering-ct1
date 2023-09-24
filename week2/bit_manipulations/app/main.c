//#include <reg_ctboard.h>
#include "utils_ctboard.h"

#define ADDR_DIP_SWITCH_31_0 0x60000200
#define ADDR_DIP_SWITCH_7_0  0x60000200
#define ADDR_LED_31_24       0x60000103
#define ADDR_LED_23_16       0x60000102
#define ADDR_LED_15_8        0x60000101
#define ADDR_LED_7_0         0x60000100
#define ADDR_BUTTONS         0x60000210

// function prototypes
uint8_t detect_changes(uint8_t value1, uint8_t value2);
uint8_t detect_rising_edge(uint8_t value1, uint8_t value2);
uint8_t detect_falling_edge(uint8_t value1, uint8_t value2);

// macros
#define setBit(value, bit) ((value) | (0x01 << (bit)))
#define clearBit(value, bit) ((value) & ~(0x01 << (bit)))
#define toggleBit(value, bit) ((value) ^ (0x01 << (bit)))
#define toggleBits(value, mask) ((value) ^ (mask))

#define getBit(value, bit) (((value) & (0x01 << (bit))) > 0)

// functions
uint8_t detect_changes(uint8_t value1, uint8_t value2){
	return value1 ^ value2;
}

uint8_t detect_rising_edge(uint8_t value1, uint8_t value2){
	uint8_t changes = detect_changes(value1, value2);
	return changes & value2;
}

uint8_t detect_falling_edge(uint8_t value1, uint8_t value2){
	uint8_t changes = detect_changes(value1, value2);
	return changes & value1;
}


int main(void)
{
	uint8_t counter3a = 0x00;
	
	uint8_t prevButtonState3c = 0x00;
	uint8_t counter3c = 0x00;
	
	uint8_t prevButtonState33 = 0x00;
	uint8_t value33 = 0x00;
	
	while (1) {
		// task 3.1
		{
			uint8_t led_value = read_byte(ADDR_DIP_SWITCH_7_0);

			led_value = clearBit(led_value, 4);
			led_value = clearBit(led_value, 5);
			led_value = setBit(led_value, 6);
			led_value = setBit(led_value, 7);

			write_byte(ADDR_LED_7_0, led_value);
		}


		// task 3.2 a
		{
			uint8_t button_values = read_byte(ADDR_BUTTONS);
			
			if(getBit(button_values, 0)) counter3a++;
			
			write_byte(ADDR_LED_15_8, counter3a);
		}

		// task 3.2 c
		{
			uint8_t button_values = read_byte(ADDR_BUTTONS);
			uint8_t risen_edges = detect_rising_edge(prevButtonState3c, button_values);

			if(getBit(risen_edges, 0)) counter3c++;
			
			write_byte(ADDR_LED_31_24, counter3c);
			
			prevButtonState3c=button_values;
		}
		
		//  taks 3.3
		{
			uint8_t button_values = read_byte(ADDR_BUTTONS);
			uint8_t risen_edges = detect_rising_edge(prevButtonState33, button_values);

			if(getBit(risen_edges, 0)){
				value33 >>= 1;
			}else if(getBit(risen_edges, 1)){
				value33 <<= 1;
			}else if(getBit(risen_edges, 2)){
				value33 = toggleBits(value33, 0x3C);
			}else if(getBit(risen_edges, 3)){
				value33 = read_byte(ADDR_DIP_SWITCH_7_0);
			}
					
			write_byte(ADDR_LED_23_16, value33);
			
			prevButtonState33=button_values;
		}		
	}
}
