/*
 * LCD_Example.c
 *
 * Created: 2018-04-08 ���� 6:54:23
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main() {
	char str1[] = "LCD Test..";
	char str2[] = "GOOD!!!";
	
	DDRC = 0xFF;		// PORTC�� ��� ���
	DDRD = 0xEE;		// PORTD�� ��� ���
	PORTC = 0xFF;
	
	LCD_Initialize();	// LCD �ʱ�ȭ �Լ� call
	LCD_Position(0,0);	// LCD�� ǥ���� ���� ��ġ ����
	LCD_Str(str1);		// LCD�� ǥ���� ���ڿ� ���
	LCD_Position(0,1);	// LCD�� ǥ���� ���� ��ġ ����
	LCD_Str(str2);		// LCD�� ǥ���� ���ڿ� ���
	while(1);
}
