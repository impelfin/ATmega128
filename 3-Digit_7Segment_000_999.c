/*
 * 3-Digit_7Segment_000_999.c
 *
 * Created: 2018-04-08 9:02:44
 * Author : Moon
 */ 

#define F_CPU 16E6
#include<avr/io.h>
#include<util/delay.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

int main(void) {
	unsigned int BCD1, BCD10, BCD100;
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	BCD1 = 0;
	BCD10 = 0;
	BCD100 = 0;	
	
	do {
		PORTD = 0xFC;		// 0b11111101;	// PORTD1	// Q1 Tr on
		PORTF = table[BCD100] ^ 0x80;
		_delay_ms(10);
		
		PORTD = 0xFA;		// 0b11111011;	// PORTD2	// Q2 Tr on 
		PORTF = table[BCD10];
		_delay_ms(10);

		PORTD = 0xF7;		// 0b11110111;	// PORTD3	// Q3 Tr on
		PORTF = table[BCD1];
		_delay_ms(10);
			
		BCD1 = BCD1 + 1;
		
		if(BCD1 == 10) {
			BCD1 = 0;
			BCD10 = BCD10 + 1;
		}
		
		if(BCD10 == 10) {
			BCD10 = 0;
			BCD100 = BCD100 + 1;
		}
		
		if(BCD100 == 10) BCD100 = 0;
	} while(1);	// End of while
}	// End of  main
