/*
 * 7Segment_All_Shift_New1.c
 *
 * Created: 2018-04-08 7:04:05
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	
	PORTA = 0xFF;
	
	unsigned char var;	
	unsigned int i;
		
	while (1) {
		var = 0b11110111;
		
		for(i=0; i<3; i++) {
			PORTD = var;
			_delay_ms(300);
			var = var >> 1;			
		}
	}
}
