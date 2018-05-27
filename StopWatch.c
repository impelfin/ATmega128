
#define F_CPU 16E6
#include <util/delay.h>
#include <avr/io.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char o_sw, n_sw, N1 = 0, N10, N100, inc=0;

int main(void)
{
	DDRD |= 0x0E;
	DDRF = 0xFF;
	
	PORTD = 0xF7;
	PORTF = 0xFF;
	
	o_sw = PIND & (1<<PIND0);
	
	while(1)
	{
		n_sw = PIND & (1<<PIND0);
		
		PORTD = 0xF7;
		PORTF = table[N1];
		_delay_ms(10);
		
		PORTD = 0xFA;
		PORTF = table[N10];
		_delay_ms(10);
		
		PORTD = 0xFD;
		PORTF = table[N100];
		_delay_ms(10);
		
		if(o_sw != 0 && n_sw == 0)inc++;

		if(inc == 1){
			N1 = N1+1;
			
			if (N1 == 10){
				N1 = 0;
				N10++;
			}
			if (N10 == 10){
				N10 = 0;
				N100++;
			}
			if (N100 == 10){
				N100 = 0;
			}
		}
		if(inc == 2) inc = 0;
		o_sw = n_sw;
	}
}