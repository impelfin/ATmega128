#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRD |= 0x0E;   // PORT D�� PD3,PD2,PD1�� ������� ����
	DDRF = 0xFF;	// PORTF�� ������� ����
	
	PORTF = 0x00;
	
	while (1) {
		PORTD = 0xF7; // 0b11110111;
		_delay_ms(300);
		PORTD = 0xFB; // 0b11111011;
		_delay_ms(300);
		PORTD = 0xFD; // 0b11111101;
		_delay_ms(300);
	}
}