#include <avr/io.h>  
#include <util/delay.h>  
  
int main(void) {  
	DDRG = 0x03; // 0b00000011

	while(1){
		PORTG = 0x01; // 0b00000001
		_delay_ms(500); 

		PORTG = 0x02; // 0b00000010
		_delay_ms(500); 
	}
	return 0;  
} 