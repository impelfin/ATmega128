/*
 * LCD_Random_Dice.c
 *
 * Created: 2018-04-16 AM 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "lcd.h"

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
	initrand();
	
	DDRA = 0xFF;		
	DDRC = 0xFF;	// PORTC는 모두 출력
	DDRD = 0xEE;   // PORTD의 PD0을 입력으로 지정
	
	PORTA = 0xFF;
	PORTC = 0xFF;
	
	unsigned char o_sw, n_sw, led, str1[16], str2[16];
	unsigned int i, num = 0;
	
	o_sw = PIND & (1<<PIND0);	
	
	while(1) {
		n_sw = PIND & (1<<PIND0);
		led = 0xFF;

		if(o_sw != 0 && n_sw == 0) {
			num = (random() % 6) + 1;
			PORTA = led << num;
		}
		o_sw = n_sw;		
		
		sprintf(str1, "Dice Game!!");
		sprintf(str2, "Your Number = %d", num);
		LCD_Display(str1, str2);
	}	
}

