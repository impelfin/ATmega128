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