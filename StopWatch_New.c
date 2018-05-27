/*
 * StopWatch_New.c
 *
 * Created: 2018-04-16 ¿ÀÀü 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include <util/delay.h>
#include <avr/io.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char o_sw, n_sw, flag = 0;
unsigned int num = 0;

void Seg3_out(int num) {
	int N100, N10, N1;
	
	N100 = num / 100;
	N10 = (num / 10) % 10;
	N1 = num % 10;
	
	PORTD = 0xFC;		// 0b11111101;	// PORTD1	// Q1 Tr on
	PORTF = table[N100];
	_delay_ms(10);
	
	PORTD = 0xFA;		// 0b11111011;	// PORTD2	// Q2 Tr on
	PORTF = table[N10];
	_delay_ms(10);
	
	PORTD = 0xF7;		// 0b11110111;	// PORTD3	// Q3 Tr on
	PORTF = table[N1];
	_delay_ms(10);
}

int main(void) {
	DDRD |= 0x0E;
	DDRF = 0xFF;
	
	PORTD = 0xF7;
	PORTF = 0xFF;
			
	o_sw = PIND & (1<<PIND0);
	
	while(1) {
		n_sw = PIND & (1<<PIND0);
		
		if(o_sw != 0 && n_sw == 0) flag++;
			
		Seg3_out(num);
		
		if(flag == 1) num++;
			
		if(num > 999) num = 0;

		if(flag == 2) flag = 0;
		
		o_sw =  n_sw;	
	}
}

