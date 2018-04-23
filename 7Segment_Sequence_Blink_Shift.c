/*
 * 7Segment_Sequence_Blink_Shift.c
 *
 * Created: 2018-04-08 7:04:05
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	unsigned char i, j, d_val, f_val;

	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정

	PORTF = 0xFF;

	while (1) {
		d_val = 0xF7;	// 0b11110111;

		for(i=0; i<3;i++) {
			PORTD = d_val;			
			
			f_val = 0xFE;	// 0b11111110;			
			
			for(j=0;j<8;j++) {
				PORTF = f_val;
				_delay_ms(300);
				f_val = f_val << 1;
			}
			d_val = d_val >> 1;
		}
	}
}
