#include <stdlib.h>
#include <reg_ctboard.h>
#include <math.h>

#define DIP_0_32 0x60000200
#define LED_0_32 0x60000100


extern void out_word(uint32_t out_address, uint32_t out_value);
extern uint32_t in_word(uint32_t in_address);


int main(void){
	while(1){
		uint32_t switch_values = in_word(DIP_0_32);
		out_word(LED_0_32, switch_values);
	}
}


