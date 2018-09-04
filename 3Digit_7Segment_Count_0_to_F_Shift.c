/*
 * 3Digit_7Segment_Count_0_to_F_Shift.c
 *
 * Created: 2018-04-16 오전 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include<avr/io.h>
#include<util/delay.h>

unsigned char table[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
unsigned char i, j, d_val; 

int main(void) {
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	
    while (1) {
		d_val = 0xF7;
		
		for(i=0; i<3; i++) {
			PORTD = d_val;
			
			for(j=0; j<16; j++) {
				PORTF = table[j];
				_delay_ms(300);
			}
			d_val = d_val >> 1;
		}
    }
}
