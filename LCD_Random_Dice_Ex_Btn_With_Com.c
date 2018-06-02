/*
 * LCD_Random_Dice_Ex_Btn_With_Com.c
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
	DDRB = 0x00;
	DDRC = 0xFF;	// PORTC�� ��� ���
	DDRD = 0xEE;   // PORTD�� PD0�� �Է����� ����
	
	PORTA = 0xFF;
	PORTC = 0xFF;
	
	unsigned char o_sw, n_sw, led, str1[16], str2[16];
	int i, num = 0, com = 0;
	
	o_sw = PINB & (1<<PINB0);	
	
	while(1) {
		n_sw = PINB & (1<<PINB0);
		led = 0xFF;

		if(o_sw != 0 && n_sw == 0) {
			num = (random() % 6) + 1;
			com = (random() % 6) + 1;
			PORTA = led << num;
		}
		o_sw = n_sw;		
		
		sprintf(str1, "User=%d vs Com=%d", num, com);
		if((num - com) > 0) { 
			sprintf(str2, "User Win!!");
		} else if((num - com) < 0) {
			sprintf(str2, "User Lose!!" );
		} else {
			sprintf(str2, "User Draw!!");			
		}
		LCD_Display(str1, str2);
	}	
}

