/*
 * LED8_BCD.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 6:58:16
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#define WDR asm("WDR")

int main(void)
{
	DDRA = 0xFF;
	DDRD = 0x00;
	DDRE = 0x00;
	PORTA = 0xFF;
	
	unsigned char sw, dip1, dip2;
	unsigned int led, n=0;
	
	while(1){
		PORTA = 0xFF;
		dip1 = PINE & (1<<PE2);
		if(dip1==0) {
			led = 0xFF;
			PORTA = led - n;
			sw = PIND & (1 << PD0);
			if(sw==0){
				n++;
				_delay_ms(300);
			} else {
			led = 0xFF;
				for(n=0; n <=0xFF; n++){
					PORTA = led - n;
					_delay_ms(500);
				}
			}
		}
		dip2 = PINE & (1<<PE3);
		if(dip2==0)
			WDR;
	}
}
