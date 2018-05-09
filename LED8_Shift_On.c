/*
 * LED8_Shift_On.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 7:27:37
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	int i;
	unsigned char led;
	
	DDRA = 0xFF;
	
	while (1) {
		led = 0xFE;
		
		for(i=0; i<8; i++) {
			PORTA = led;
			_delay_ms(500);
			led = led << 1;
		}
	}
}
