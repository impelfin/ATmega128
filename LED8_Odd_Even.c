/*
 * LED8_Odd_Even.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 7:20:38
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRA = 0xFF;
	while (1) {
		PORTA = 0x55;
		_delay_ms(500);
		PORTA = 0xAA;
		_delay_ms(500);
	}
}
