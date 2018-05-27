/*
 * Random_3-Digit_7Segment.c
 *
 * Created: 2018-04-16 AM 1:38:30
 * Author : MACBOOK
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/eeprom.h>

#define  ADC_REG 0x78

struct adc 
{
	union
	{
		struct
		{
			uint8_t adc_l;
			uint8_t adc_h;
		};		
		uint16_t adc;
	};	
	uint8_t adcsr_a;
	uint8_t adcsr_b;
	uint8_t admux;	
};

volatile struct adc *const adc = (void*)ADC_REG;

#define AREF_AVCC	0x40
#define AREF_1_1V	0xC0
#define ADLAR		0x20
#define MUX_MASK	0x0F

enum adc_mux
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ADC8	
};

#define ADEN	0x80
#define ADSC	0x40
#define ADATE	0x20
#define ADIF	0x10
#define ADIE	0x08

enum adc_prescaler
{
	DIV_0,
	DIV_2,
	DIV_4,
	DIV_8,
	DIV_16,
	DIV_32,
	DIV_64,
	DIV_128
};

void adc_init(void)
{
	adc->admux = AREF_1_1V | ADC8;
	adc->adcsr_a = ADEN | DIV_8;
}

uint16_t adc_read(void)
{
	adc->adcsr_a |= ADSC;
	while(adc->adcsr_a & ADSC);
	return adc->adc;
}

typedef unsigned char u_char;

u_char table[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
u_char N100 = 0, N10 = 0, N1 = 0, o_sw, n_sw, num = 0;
	
void Seg3_out(int num) {
	int i, n, N100, N10, N1;
	
	N100 = num / 100;
	N10 = (num / 10) % 10;
	N1 = num % 10;
	
	for (i=0; i<3; i++) {
		if (i == 0) n = N1;
		if (i == 1) n = N10;
		if (i == 2) n = N100;
		
		PORTD = 0xF7 >> i; // 0b11110111;	// PORTD3	// Q3 Tr on
		PORTF = table[n];
		_delay_ms(10);
	}
}

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
	DDRD |= 0x0E;   // PORT DAC PD3,PD2,PD1A¡í Aa¡¤A, PD0A¡í AO¡¤AA¢¬¡¤I AoA¢´
	DDRE |= 0x00;	// PORT EAC PE3, PE2¢¬| AO¡¤AA¢¬¡¤I AoA¢´ 
	DDRF = 0xFF;	// PORTF¢¬| Aa¡¤AA¢¬¡¤I AoA¢´
	
	PORTA = 0xFF;
	PORTD = 0xF7;		/* Q3 Tr on */
	PORTF = 0xFF;
	PORTE = 0x00;
//	srand(adc_read());
	initrand();
	
	o_sw = PIND & (1<<PIND0);	
	
	while(1) {
		Seg3_out(num);
		n_sw = PIND & (1<<PIND0); 
		if(o_sw != 0 && n_sw == 0) 
			num = random() % 1000;			
		o_sw = n_sw;
	}		
}

