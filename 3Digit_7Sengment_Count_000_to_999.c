/*
 * 3Digit_7Sengment_Count_000_to_999.c
 *
 * Created: 2018-04-16 ���� 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include<avr/io.h>
#include<util/delay.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char i, j, d_val; 

void Seg3_out(int);

int main(void) {
	DDRD |= 0x0E;   // PORT D�� PD3,PD2,PD1�� ������� ����
	DDRF = 0xFF;	// PORTF�� ������� ����
	
	PORTF = 0xFF;
	
	int num = 0;
	
    while (1) {		
		Seg3_out(num);
		num++;
		if(num > 999) num = 0;
	}
}

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