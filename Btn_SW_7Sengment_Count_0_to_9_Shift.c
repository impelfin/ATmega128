

#define F_CPU 16E6
#include <util/delay.h>
#include <avr/io.h>

unsigned char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char o_sw, n_sw, num = 0;
	
int main(void)
{
	DDRD |= 0x0E;
	DDRF = 0xFF;
	
	PORTD = 0xF7;
	PORTF = 0xFF;
	
	o_sw = PIND & (1<<PIND0);
	
    while(1)
    {
		PORTF = table[num];
		
        n_sw = PIND & (1<<PIND0);
		if(o_sw != 0 && n_sw == 0){
			num = (num + 1) % 10;
			if(num == 0){
				PORTD = PORTD >>1;
				num = 1;
			}
		if (PORTD == 0x1E) PORTD = 0xF7;	
		}
		o_sw = n_sw;
    }
}