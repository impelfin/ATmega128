/*
 * Random_3-Digit_7Segment.c
 *
 * Created: 2018-04-16 AM 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/eeprom.h>

typedef unsigned char u_char;

u_char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
u_char o_sw, n_sw;
unsigned int num = 0;
	
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

void initrand() 
{
	uint32_t state;
	static uint32_t EEMEM sstate;
	state = eeprom_read_dword(&sstate);
	if(state == 0xffffffUL)
		state = 0xDEADBEEFUL;
	srandom(state);
	eeprom_write_dword(&sstate, random());	
}

int main(void) {
	DDRA = 0xFF;
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력, PD0을 입력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정
	
	PORTA = 0xFF;
	PORTD = 0xF7;		/* Q3 Tr on */
	PORTF = 0xFF;
	PORTE = 0x00;
	initrand();
	
	o_sw = PIND & (1<<PIND0);	
	
	while(1) {
		Seg3_out(num);
		n_sw = PIND & (1<<PIND0); 
		if(o_sw != 0 && n_sw == 0) 
			num = random() % 1000;			
		o_sw = n_sw;
	}		
}

