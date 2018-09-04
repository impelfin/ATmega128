/*
 * 3Digit_7Sengment_Count_00_to_99.c
 *
 * Created: 2018-04-16 오전 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include<avr/io.h>
#include<util/delay.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char i, j, d_val; 

void Seg2_out(int);

int main(void) {
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	
	PORTF = 0xFF;
	
	int num = 0;
	
    while (1) {		
		Seg2_out(num);
		num++;
		if(num > 99) num = 0;
	}
}

void Seg2_out(int num) {
	int N10, N1;
	
	N10 = num / 10;
	N1 = num % 10;
	
	PORTD = 0xFA;		// 0b11111011;	// PORTD2	// Q2 Tr on
	PORTF = table[N10];
	_delay_ms(10);
		
	PORTD = 0xF7;		// 0b11111011;	// PORTD2	// Q2 Tr on
	PORTF = table[N1];
	_delay_ms(10);
}
