/*
 * LED8_Blink_XOR.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 9:27:50
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRA = 0xFF;
	PORTA = 0xFF;

	while (1) {
		PORTA = PORTA ^ 0xFF;
		_delay_ms(500);
	}
}
