/*
 * LED8_Array_Swing.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 6:48:54
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	
	DDRA = 0xFF; // 0b11111111
	
	uint8_t data[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	int i;
	
	while(1) {	
		for(i = 0; i < 8; i++) {
			PORTA = ~(data[i]);
			_delay_ms(300);
		}
		for(i = 7; i >= 0; i--) {
			PORTA = ~(data[i]);
			_delay_ms(300);
		}
	}
	return 0;
}
