/*
 * LCD_Btn_Pressed.c
 *
 * Created: 2018-04-08 ���� 6:54:23
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main() {
	DDRC = 0xFF;		// PORTC�� ��� ���
	DDRD = 0xEE;		// PORTD�� ��� ���
	
	PORTC = 0xFF;
	
	unsigned char key, str1[16], str2[16]; 
	unsigned int btn_no;	
	
	while(1) {
		key = PIND & (1<<PIND0);

		if(key == 0x01) btn_no = 0;

		sprintf(str1, "Port B Reg : %d", key);
		sprintf(str2, "Btn %d Pressed!!", btn_no);
			
		LCD_Initialize();	// LCD �ʱ�ȭ �Լ� call
		LCD_Position(0,0);	// LCD�� ǥ���� ���� ��ġ ����
		LCD_Str(str1);		// LCD�� ǥ���� ���ڿ� ���
		LCD_Position(0,1);	// LCD�� ǥ���� ���� ��ġ ����
		LCD_Str(str2);		// LCD�� ǥ���� ���ڿ� ���
	}
}
