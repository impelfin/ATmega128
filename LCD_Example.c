/*
 * LCD_Example.c
 *
 * Created: 2018-04-08 오후 6:54:23
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>

#define RS_0  (PORTD & 0xDF)
#define RS_1  (PORTD | 0x20)
#define RW_0  (PORTD & 0xBF)
#define RW_1  (PORTD | 0x40)
#define LCDEN_0  (PORTD & 0x7F)
#define LCDEN_1  (PORTD | 0x80)
#define LCD_data   PORTC

void LCD_Comm(char c) {
	PORTD = RS_0;
	PORTD = RW_0;
	PORTD = LCDEN_1;
	_delay_us(50);
	LCD_data = c;
	_delay_us(50);
	PORTD = LCDEN_0;
}

void LCD_Data(char c) {
	PORTD = RS_1;
	PORTD = RW_0;
	PORTD = LCDEN_1;
	_delay_us(50);
	LCD_data = c;
	_delay_us(50);
	PORTD = LCDEN_0;
}

void LCD_initialize() {
	_delay_ms(20);
	LCD_Comm(0x38);
	_delay_ms(5);
	LCD_Comm(0x38);
	_delay_us(200);
	LCD_Comm(0x38);
	_delay_us(50);
	LCD_Comm(0x0e);
	_delay_us(50);
	LCD_Comm(0x01);
	_delay_ms(2);
	LCD_Comm(0x06);
	_delay_us(50);
}

void LCD_CHAR(char c) {
	LCD_Data(c);
	_delay_ms(1);
}

void LCD_STR(char *str) {
	while(*str) {
		LCD_CHAR(*str);
		str++;
	}
}

void LCD_position(unsigned char row, unsigned char col) {
	LCD_Comm(0x80|(row + col*0x40));
}

void LCD_clear() {
	LCD_Comm(0x01);
	_delay_ms(2);
}

int main() {
	char str1[] = "LCD Test..";
	char str2[] = "GOOD!!!";
	
	DDRC = 0xFF;		// PORTC는 모두 출력
	DDRD = 0xEE;		// PORTD는 모두 출력
	PORTC = 0xFF;
	
	LCD_initialize();	// LCD 초기화 함수 call
	LCD_position(0,0);	// LCD에 표시할 문자 위치 지정
	LCD_STR(str1);		// LCD에 표시할 문자열 출력
	LCD_position(0,1);	// LCD에 표시할 문자 위치 지정
	LCD_STR(str2);		// LCD에 표시할 문자열 출력
	while(1);
}
