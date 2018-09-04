/*
 * 3Digit_7Sengment_Count_0_to_9.c
 *
 * Created: 2018-04-16 오전 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include<avr/io.h>
#include<util/delay.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned int i;

int main(void) {
	DDRD |= 0x0E;   // PORT D의 PD3,PD2,PD1을 출력으로 지정
	DDRF = 0xFF;	// PORTF를 출력으로 지정

	PORTD = 0xF7;		/* Q3 Tr on */
	
    while (1) {
		for(i=0; i<10; i++) {
			PORTF = table[i];
			_delay_ms(300);
		}
    }
}
