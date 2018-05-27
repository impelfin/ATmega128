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
	DDRA = 0xFF;		
	DDRC = 0xFF;	// PORTC는 모두 출력
	DDRD = 0xEE;   // PORTD의 PD0을 입력으로 지정
	
	PORTA = 0xFF;
	PORTC = 0xFF;

	initrand();
	
	unsigned char o_sw, n_sw, led, str1[16], str2[16];
	unsigned int i, num = 0;
	
	o_sw = PIND & (1<<PIND0);	
	
	while(1) {
		n_sw = PIND & (1<<PIND0);
		led = 0xFE;

		if(o_sw != 0 && n_sw == 0) {
			num = (random() % 6) + 1;
			for(i = 0;i < num; i++) {
				PORTA = led;
				led = led << 1;
			}
		}
		o_sw = n_sw;		
		
		sprintf(str1, "Dice Game!!");
		sprintf(str2, "Your Number = %d", num);
		
		LCD_initialize();	// LCD 초기화 함수 call
		LCD_position(0,0);	// LCD에 표시할 문자 위치 지정
		LCD_STR(str1);		// LCD에 표시할 문자열 출력
		LCD_position(0,1);	// LCD에 표시할 문자 위치 지정
		LCD_STR(str2);		// LCD에 표시할 문자열 출력
	}	
}

