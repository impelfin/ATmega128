/*
 * Btn_SW_LED8_Sequence_Blink_Array.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 7:04:05
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

flash unsigned char led[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

int main(void) {
	unsigned char o_sw, n_sw;
	unsigned char st = 0;

	DDRA = 0xFF;
	DDRD = 0x00;
	
	PORTA = led[st];
	
	o_sw = PIND & (1<<PIND0);
	
	while (1) {
		n_sw = PIND & (1<<PIND0);
		if(o_sw != 0 && n_sw == 0) {
			st = (st + 1) % 8;
			PORTA = led[st];
		}
		o_sw = n_sw;
	}
}
