/*
 * LCD_Ex_Btn_Pressed.c
 *
 * Created: 2018-04-08 오후 6:54:23
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main() {
	DDRC = 0xFF;		// PORTC는 모두 출력
	DDRD = 0xEE;		// PORTD는 모두 출력
	DDRB = 0x00;
	
	PORTC = 0xFF;
	
	unsigned char key, str1[16], str2[16]; 
	unsigned int btn_no;	
	
	while(1) {
		key = PINB & 0x0F;

		if(key == 0x08) btn_no = 1;
		else if(key == 0x04) btn_no = 2;
		else if(key == 0x02) btn_no = 3;
		else if(key == 0x01) btn_no = 4;

		sprintf(str1, "Port B Reg : %d", key);
		sprintf(str2, "Btn %d Pressed!!", btn_no);
			
		LCD_initialize();	// LCD 초기화 함수 call
		LCD_position(0,0);	// LCD에 표시할 문자 위치 지정
		LCD_STR(str1);		// LCD에 표시할 문자열 출력
		LCD_position(0,1);	// LCD에 표시할 문자 위치 지정
		LCD_STR(str2);		// LCD에 표시할 문자열 출력
	}
}
