#include "header.h"

///////////////    EEPROM TESTING   /////////////

void eeprom_testing(void)
{
	unsigned char x;
	unsigned char temp = 0;
abc:
	uart_string("\r\n\r\nConnect SCL To P3.2\r\nConnect SDA To P3.3\r\nConnect EEPROM:-AT24C08 Or M24C08\r\nPress ENTER To Start Loopback\r\n");

	x = uart_rxd();

	if (x == '\r')
	{
		uart_string("\r\nLoopBack Started\r\n(Press ENTER For Come Out Of LoopBack)\r\n");
		while (1)
		{

			x = uart_rxd();
			if (x == '\r')
			{
				uart_string("\r\n");
				goto xyz_;
			}
			i2c_byte_write(0xA0, 0x10, x);
			delay(50);
			temp = (unsigned char)i2c_byte_read(0xA0, 0x10);

			uart_txd(temp);
			uart_string("\r\nPlease Wait ");
			for (temp = 0, x = 5; temp < 6; x--, temp++)
			{

				uart_txd(x + 48);
				uart_string(" Sec");
				delay(1000);
				uart_string("\b\b\b\b\b");
			}
			uart_string("\b\b\b\b\b\b\b\b\b\b\b\b\b");
			uart_string("\r\nEnter New Char:\r\n");
		}
	xyz_:
		uart_string("\r\nIs Every Charector Prints Properly (y/n)??\r\n");
	xyz:
		x = uart_rxd();

		if ((x == 'y') || (x == 'Y'))
		{
			uart_string("\r\n");
			return;
		}
		else if ((x == 'n') || (x == 'N'))
		{
			goto last;
		}
		else
		{
			uart_string("\r\nPlease Choose (y/n) Only!!\r\n");
			goto xyz;
		}
	}
	else
	{
		uart_string("\r\nPlease Press Enter Only\r\n");
		goto abc;
	}

last:
	uart_string("\r\n\r\nMake Sure\r\n1.EEPROM(AT24C08 Or M24C08) Is Available On Board\r\n2.Each Lag Of IC Are Proper\r\n3.SCL Connected Properly To P3.2\r\n4.SDA Connected Properly To P3.3\r\nAgain");
	goto abc;
}
