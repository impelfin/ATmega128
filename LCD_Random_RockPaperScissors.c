/*
 * LCD_Random_RockPaperScissors.c
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
	DDRB = 0x00;
	DDRC = 0xFF;	// PORTC는 모두 출력
	DDRD = 0xFE;   // PORTD의 PD0을 입력으로 지정
	
	PORTA = 0xFF;
	PORTC = 0xFF;		
	PORTD = 0xFF;

	initrand();
	
	unsigned char key, led, str1[16], str2[16];
	int i, num = 0, com = 0;
	
	while(1) {
		key = PINB & 0x0F;
		led = 0xFE;
		
		if(key == 0x08) {
			num = 1;
			com = (random() % 3) + 1;
		} else if(key == 0x04) {
			num = 2;
			com = (random() % 3) + 1;
		} else if(key == 0x02) {
			num = 3;
			com = (random() % 3) + 1;
		} else if(key == 0x01) {
			num = (random() % 3) + 1;
			com = (random() % 3) + 1;
		}
		
		if(num == 1) PORTA = 0x3F;
		if(num == 2) PORTA = 0xE7;
		if(num == 3) PORTA = 0xFC;
		
		sprintf(str1, "User=%d vs Com=%d", num, com);
		
		if((num - com) == -2 || (num - com) == 1) { 
			sprintf(str2, "User Win!!");
			PORTD = 0x00;
			_delay_ms(50);
			PORTD = 0xFF;
		} else if((num - com) == -1 || (num - com) == 2) {
			sprintf(str2, "User Lose!!" );
		} else {
			sprintf(str2, "User Draw!!");			
		}
		
		LCD_Initialize();	// LCD 초기화 함수 call
		LCD_Position(0,0);	// LCD에 표시할 문자 위치 지정
		LCD_Str(str1);		// LCD에 표시할 문자열 출력
		LCD_Position(0,1);	// LCD에 표시할 문자 위치 지정
		LCD_Str(str2);		// LCD에 표시할 문자열 출력
	}	
}

