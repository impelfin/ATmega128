/*
 * Btn_SW_LED8_Swing.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 7:04:05
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	unsigned char o_sw, n_sw;
	unsigned char led = 0xFE;
	
	DDRA = 0xFF;
	DDRD = 0x00;
	
	PORTA = led;
	
	o_sw = PIND & (1<<PIND0);
	
	while (1) {
		n_sw = PIND & (1<<PIND0);
		if(o_sw != 0 && n_sw == 0) {
			led = (led<<1) | 0x01;
			if(led == 0xFF) led = 0xFE;
			
			PORTA = led;
		}
		o_sw = n_sw;
	}
}
