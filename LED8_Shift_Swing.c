/*
 * LED8_Shift_Swing.c
 *
 * Created: 2018-04-08 ¿ÀÈÄ 6:54:23
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	
	int i;
	unsigned char led;
	while (1)
	{
		led = 0xFE;
		
		for(i = 0;i < 8; i++) {
			PORTA = led;
			_delay_ms(300);
			
			led = led << 1;
			led = led | 0x01;
		}
	}
}
