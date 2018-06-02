/*
 * LCD_Btn_Pressed_All_Funtion.c
 *
 * Created: 2018-04-08 오후 6:54:23
 * Author : Moon
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

unsigned char o_sw, n_sw, str1[16], str2[16], page = 0;
int i;

int main() {
	DDRA = 0xFF;
	DDRC = 0xFF;		// PORTC는 모두 출력
	DDRD = 0xEE;		// PORTD는 모두 출력
	
	PORTA = 0xFF;
	PORTC = 0xFF;
	
	o_sw = PIND & (1<<PIND0);
	
	while(1) {
		n_sw = PIND & (1<<PIND0);

		if(o_sw !=0 && n_sw == 0 ) page++;
		
		if(page == 1) {
			PORTA = 0x7F;
			LCD_Funtion_On();
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "All Fx Enabled");		
			LCD_Display(str1, str2);	
		} else if (page == 2) {
			PORTA = 0xBF;
			LCD_Clear();
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "LCD Cleared");
			LCD_Display(str1, str2);
			_delay_ms(100);	
		} else if (page == 3) {
			PORTA = 0xDF;
			LCD_Cursor_Home();
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "LCD Cursor Home");
			LCD_Display(str1, str2);
		} else if (page == 4) {
			PORTA = 0xEF;
			LCD_Entry_Bit_Set();
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "Entry Bit Set");
			LCD_Display(str1, str2);
		} else if (page == 5) {
			PORTA = 0xF7;
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "Display Shift Right");
			LCD_Display(str1, str2);
			for(i=0; i<=16; i++) {
				LCD_Display_Shift(1);
				_delay_ms(500);
			}
			LCD_Clear();
			page++;
			PORTA = 0xFB;
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "Display Shift Left");
			LCD_Display(str1, str2);
			_delay_ms(500);
			for(i=0; i<=16; i++) {
				LCD_Display_Shift(0);
				_delay_ms(500);
			}
			LCD_Clear();
			page++;
			PORTA = 0xFD;
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "Cursor Right");
			LCD_Display(str1, str2);
			LCD_Cursor_Home();
			for(i=0; i<=16; i++) {
				LCD_Cursor_shift(1);
				_delay_ms(500);
			}
			LCD_Clear();
			page++;
			PORTA = 0xFE;
			sprintf(str1, "Page No = %d", page);
			sprintf(str2, "Cursor Left");
			LCD_Display(str1, str2);
			_delay_ms(500);
			LCD_Position(16,0);
			for(i=0; i<=16; i++) {
				LCD_Cursor_shift(0);
				_delay_ms(500);
			}
		} 
		if(page == 8) page = 1;
		o_sw = n_sw;
	}
}
