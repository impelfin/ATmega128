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

void LCD_Initialize() {
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

void LCD_Char(char c) {
	LCD_Data(c);
	_delay_ms(1);
}

void LCD_Str(char *str) {
	while(*str) {
		LCD_Char(*str);
		str++;
	}
}

void LCD_Position(unsigned char row, unsigned char col) {
	LCD_Comm(0x80|(row + col*0x40));
}

void LCD_Clear() {
	LCD_Comm(0x01);
	_delay_ms(2);
}

void LCD_Cursor_Home(void) {
	LCD_Comm(0x02);		// Cursor Home
	_delay_ms(2);		// 1.64ms �̻� �ð� ����
}

void LCD_Funtion_On() {
	LCD_Comm(0x0e);		// ��� ����� ON �Ѵ�.
	_delay_ms(2);		// 1.64�� �̻��� ��ٸ�
}

void LCD_Entry_Bit_Set() {
	LCD_Comm(0x06);		// LCD Clear
	_delay_ms(2);		// 1.64�� �̻��� ��ٸ�
}

void LCD_Display(str1, str2) {
	LCD_Initialize();	// LCD �ʱ�ȭ �Լ� call
	LCD_Position(0,0);	// LCD�� ǥ���� ���� ��ġ ����
	LCD_Str(str1);		// LCD�� ǥ���� ���ڿ� ���
	LCD_Position(0,1);	// LCD�� ǥ���� ���� ��ġ ����
	LCD_Str(str2);		// LCD�� ǥ���� ���ڿ� ���
}

#define RIGHT 1
#define LEFT 0

void LCD_Display_Shift(char p) {// ���÷��� ����Ʈ (5)
	if(p == RIGHT) {		// ǥ�� ȭ�� ��ü�� ���������� �̵�
		LCD_Comm(0x1C);		// * A���� C�� �ٲ�
		_delay_us(50);		// �ð� ����
	} else if(p == LEFT) {	// ǥ�� ȭ�� ��ü�� �������� �̵�
		LCD_Comm(0x18);
		_delay_us(50);
	}
}

void LCD_Cursor_shift(char p) {
	if(p == RIGHT) {
		LCD_Comm(0x14);
		_delay_us(50);
	} else if(p == LEFT) {
		LCD_Comm(0x10);
		_delay_us(50);
	}
}
