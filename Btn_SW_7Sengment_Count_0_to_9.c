/*
 * Btn_SW_7Sengment_Count_0_to_9.c
 *
 * Created: 2018-04-16 ���� 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include<avr/io.h>
#include<util/delay.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char o_sw, n_sw, num = 0;

int main(void) {
	DDRD |= 0x0E;   // PORT D�� PD3,PD2,PD1�� ���, PD0�� �Է����� ����
	DDRF = 0xFF;	// PORTF�� ������� ����

	PORTD = 0xF7;		/* Q3 Tr on */
	PORTF = 0xFF;
	
	o_sw = PIND & (1<<PIND0);
	
    while (1) {
		PORTF = table[num];
		
		n_sw = PIND & (1<<PIND0);
		
		if(o_sw != 0 && n_sw == 0) {
			num = (num + 1) % 10;
		}
		o_sw = n_sw;
	}
}