/*
 * LED1_Blink.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 9:02:44
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRA = 0xFF;

	while (1) {
		PORTA = 0xFE;
		_delay_ms(500);
		PORTA = 0xFF;
		_delay_ms(500);
	}
}
