/*
 * LCD_Ex_Btn_Pressed.c
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
			
		LCD_initialize();	// LCD �ʱ�ȭ �Լ� call
		LCD_position(0,0);	// LCD�� ǥ���� ���� ��ġ ����
		LCD_STR(str1);		// LCD�� ǥ���� ���ڿ� ���
		LCD_position(0,1);	// LCD�� ǥ���� ���� ��ġ ����
		LCD_STR(str2);		// LCD�� ǥ���� ���ڿ� ���
	}
}
