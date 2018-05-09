/*
 * 7Segment_Sequence_Blink.c
 *
 * Created: 2018-04-08 7:04:05
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	unsigned char i, f_val;

	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	
	PORTD = 0xF7;		/* Q3 Tr on */
	
	while (1) {
		PORTF = 0xFF;
		f_val = 0b11111110;
		for(i=0;i<8;i++) {
			PORTF = f_val;
			_delay_ms(300);
			f_val = f_val << 1;
		}
	}
}
