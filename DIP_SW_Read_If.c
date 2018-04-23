/*
 * DIP_SW_Read_If.c
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
		
		if(key == 0x0C)	PORTA = 0x00;	// 0b00001100:
		if(key == 0x08) PORTA = 0x0F;	// 0b00001000:
		if(key == 0x04) PORTA = 0xF0;	// 0b00000100:
		if(key == 0x00) PORTA = 0xFF;	// 0b00000000:
	}
}

