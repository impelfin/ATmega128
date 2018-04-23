/*
 * DIP_SW_Read_Switch.c
 *
 * Created: 2018-04-09 ¿ÀÀü 1:18:22
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	unsigned char key;
	
	DDRA = 0xFF;
	DDRE = 0x00;
	
	PORTA = 0xFF;
	
	while (1) {
		key = PINE & 0x0C;	// 0b00001100
		
		switch(key) {
			case 0x0C:	// 0b00001100:
				PORTA = 0x00;
				break;
			case 0x08:	// 0b00001000:
				PORTA = 0x0F;
				break;
			case 0x04:	// 0b00000100:
				PORTA = 0xF0;
				break;
			case 0x00:	// 0b00000000:
				PORTA = 0xFF;
				break;
		}
	}
}

