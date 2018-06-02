/*
 * LCD_Btn_Pressed.c
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
	
	PORTC = 0xFF;
	
	unsigned char key, str1[16], str2[16]; 
	unsigned int btn_no;	
	
	while(1) {
		key = PIND & (1<<PIND0);

		if(key == 0x01) btn_no = 0;

		sprintf(str1, "Port B Reg : %d", key);
		sprintf(str2, "Btn %d Pressed!!", btn_no);
			
		LCD_Initialize();	// LCD 초기화 함수 call
		LCD_Position(0,0);	// LCD에 표시할 문자 위치 지정
		LCD_Str(str1);		// LCD에 표시할 문자열 출력
		LCD_Position(0,1);	// LCD에 표시할 문자 위치 지정
		LCD_Str(str2);		// LCD에 표시할 문자열 출력
	}
}
