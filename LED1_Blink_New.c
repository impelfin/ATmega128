/*
 * LED1_Blink_New.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 9:57:54
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRA = 0xFF;
	PORTA = 0xFF;
	
	while (1) {
		PORTA |= 1<<PORTA0;
		_delay_ms(500);
		PORTA &= ~(1<<PORTA0);
		_delay_ms(500);
	}
}