/*
 * 3Digit_7Sengment_Count_000_to_999_for.c
 *
 * Created: 2018-04-16 오전 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include<avr/io.h>
#include<util/delay.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char num, d_val, o_sw, n_sw, st = 0; 

void Seg3_out(int num) {
	int i, n, N100, N10, N1;
	
	N100 = num / 100;
	N10 = (num / 10) % 10;
	N1 = num % 10;
	
	for (i=0; i<3; i++) {
		if (i == 0) n = N1;
		if (i == 1) n = N10;
		if (i == 2) n = N100;
		
		PORTD = 0xF7 >> i; // 0b11110111;	// PORTD3	// Q3 Tr on
		PORTF = table[n];
		_delay_ms(10);
	}
}

void tact_pressed(int st) {
	if(st == 1) {
		Seg3_out(num);
		num++;
		if(num > 999) num = 0;
		_delay_ms(10);
	} 
	if (st == 0) {
		Seg3_out(num);
	}	
}

int main(void) {
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	PORTF = 0xFF;
	int num = 0;
	
	o_sw = PIND & (1<<PIND0);
    while (1) {		
		Seg3_out(num);
		n_sw = PIND & (1<<PIND0);
		if(st == 0 && o_sw != 0 && n_sw == 0) {
			tact_pressed(1);
		}			
		if(st == 1 && o_sw != 0 && n_sw == 0) {
			tact_pressed(0);							
		}	
		o_sw = n_sw;		
	}
}
