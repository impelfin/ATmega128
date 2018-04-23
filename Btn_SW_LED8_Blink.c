/*
 * Btn_SW_LED8_Blink.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 11:07:23
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	unsigned char sw;
	
	DDRA = 0xFF;
	DDRD = 0x00;
	
	PORTA = 0xFF;
	
	while (1) {
		sw = PIND & (1<<PIND0);
		if(sw != 0 ) PORTA = 0xFF;
		else PORTA = 0x00;
	}
}
