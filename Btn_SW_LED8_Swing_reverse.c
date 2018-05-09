#define F_CPU 16E6
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	unsigned char o_sw, n_sw, d_sw;
	unsigned char led = 0xFE;
	
	DDRA= 0xFF;
	DDRD = 0x00;
	DDRE = 0x00;
	
	PORTA = led;

	o_sw = PIND & (1<<PIND0);

    while(1) {
        n_sw = PIND & (1<<PIND0);
		d_sw = PINE & (1<<PINE2);
		
		if(o_sw != 0 && n_sw == 0 && d_sw == 0) {
			led = (led<<1) | 0x01;
			if(led == 0xFF) led = 0xFE;
			PORTA = led;	
		}
			
		if(o_sw != 0 && n_sw == 0 && d_sw != 0) {
			led = (led>>1) | 0x80;
			if(led == 0xFF) led = 0x7F;
			PORTA = led;
		}
		o_sw = n_sw;
	}
}