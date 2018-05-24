/*
 * Btn_DIP_7Sengment_Count_000_to_999_New.c
 *
 * Created: 2018-04-16 오전 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char u_char;

u_char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
u_char N100 = 0, N10 = 0, N1 = 0;
u_char pos = 0;		// 0 : 1자리, 1 : 10자리, 2 : 100자리

void Seg3_out(void);
void tact_pressed(void);
void dip1_changed(void);

int main(void) {
	DDRA = 0xFF;
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력, PD0을 입력으로 지정
	DDRE |= 0x00;	// PORT E의 PE3, PE2를 입력으로 지정 
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	
	PORTA = 0xFF;
	PORTD = 0xF7;		/* Q3 Tr on */
	PORTF = 0xFF;
	PORTE = 0x00;
	
	u_char o_sw, n_sw, dip1;
	
	o_sw = PIND & (1<<PIND0);	

	while(1) {
		Seg3_out();	
		
		n_sw = PIND & (1<<PIND0); 

		dip1 = PINE & 0x0C;
		if(n_sw == o_sw) continue;
		
		if(dip1 == 0x00 && o_sw != 0 && n_sw == 0) {
			tact_pressed();
			PORTA = 0xF0;
		} else if((dip1 == 0x04 || dip1 == 0x08 || dip1 == 0x0C) && o_sw != 0 && n_sw == 0) {
			dip1_changed();
			PORTA = 0x0F;
		}
		o_sw = n_sw;
	}
}

void tact_pressed() {
	if(pos == 0) N1 = (N1 + 1) % 10;
	else if(pos == 1) N10 = (N10 + 1) % 10;
	else N100 = (N100 + 1) % 10;
}

void dip1_changed() {
	pos = (pos + 1) % 3;
}

void Seg3_out() {
	PORTD = 0xFC;		// 0b11111101;	// PORTD1	// Q1 Tr on
	if(pos == 0) {
		PORTF = table[N100];
		_delay_ms(10);
	
		PORTD = 0xFA;		// 0b11111011;	// PORTD2	// Q2 Tr on
		PORTF = table[N10];
		_delay_ms(10);
	
		PORTD = 0xF7;		// 0b11110111;	// PORTD3	// Q3 Tr on
		PORTF = table[N1] ^ 0x80;
		_delay_ms(10);
		PORTA = 0xFF;
	} else if(pos == 1) {
		PORTF = table[N100];
		_delay_ms(10);
		
		PORTD = 0xFA;		// 0b11111011;	// PORTD2	// Q2 Tr on
		PORTF = table[N10] ^ 0x80;
		_delay_ms(10);
		
		PORTD = 0xF7;		// 0b11110111;	// PORTD3	// Q3 Tr on
		PORTF = table[N1];
		_delay_ms(10);
		PORTA = 0xFF;
	} else {
		PORTF = table[N100] ^ 0x80;
		_delay_ms(10);
		
		PORTD = 0xFA;		// 0b11111011;	// PORTD2	// Q2 Tr on
		PORTF = table[N10];
		_delay_ms(10);
		
		PORTD = 0xF7;		// 0b11110111;	// PORTD3	// Q3 Tr on
		PORTF = table[N1];
		_delay_ms(10);
		PORTA = 0xFF;
	}
}
