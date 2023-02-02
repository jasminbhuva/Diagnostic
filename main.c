#include "header.h"
void main()
{
	unsigned char x;
	uart_init(9600);
	// uart_init();
	lcd_init();
	while (1)
	{
		x = menu_display();
		switch (x)
		{
		case 'a':
		case 'A':
			led_testing();
			break;
		case 'b':
		case 'B':
			switch_testing();
			break;
		case 'c':
		case 'C':
			lcd_testing();
			break;
		case 'd':
		case 'D':
			keypad_testing();
			break;
		case 'e':
		case 'E':
			eeprom_testing();
			break;
		case 'f':
		case 'F':
			adc_testing();
			break;
		default:
			uart_string("\r\n");
		}
	}
}