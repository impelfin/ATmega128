/*
 * Btn4_Led8.c
 *
 * Created: 2018-05-17 ¿ÀÈÄ 2:48:18
 *  Author: 2415-00
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	unsigned char key;
	
	DDRA = 0xFF;
	DDRB = 0x00;
	
	PORTA = 0xFF;
	
	while (1) {
		key = PINB & 0x0F;
		
		if(key == 0x08) PORTA = 0x3F;	
		else if(key == 0x04) PORTA = 0xCF;	
		else if(key == 0x02) PORTA = 0xF3;	
		else if(key == 0x01) PORTA = 0xFC;	
	}
}
