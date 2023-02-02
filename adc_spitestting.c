//#include<reg51.h>
#include "header.h"
sbit CLK = P3 ^ 4;
sbit Do = P3 ^ 5;
sbit Di = P3 ^ 6;
sbit CS = P3 ^ 7;
bit d1, d0;
bit flag = 0;
void adc_testing(void)
{

	unsigned int val = 0;
	char i;
	float f;
	unsigned char x, ch;
	lcd_cmd(0x0c);
	uart_string("\r\n\r\nConnect:\r\nP3.4-P3.7 To CLK,DOUT,DI,CS (MCP3204 ADC) Respectivly\r\n");
	uart_string("Also Connect LCD:\r\nLCD D0-D7 T0 P0-P7\r\nRS To P2.0\r\nRW To P2.1\r\nEN To P2.2\r\n");
start_:
	uart_string("Choose Channel 0/1/2/3\r\n");
start:
	x = uart_rxd();
	if (x == '0')
	{
		lcd_string("CH:0");
		ch = 0;
		d0 = 0, d1 = 0;
	}
	else if (x == '1')
	{
		lcd_string("CH:1");
		ch = 1;
		d0 = 1, d1 = 0;
	}
	else if (x == '2')
	{
		lcd_string("CH:2");
		ch = 2;
		d0 = 0, d1 = 1;
	}
	else if (x == '3')
	{
		lcd_string("LIGHT INTENSITY");
		ch = 3;
		d0 = 1, d1 = 1;
	}
	else
	{
		uart_string("\r\nPlease Enter 0/1/2/3 Only\r\n");
		goto start;
	}
	uart_string("\r\nStart Testing\r\nPress ENTER For Exit");

	uart_en(); // uart_intureeput enable
	flag = 0;
	while (1)
	{

		CS = 0;
		CLK = 0;
		Di = 1;
		CLK = 1; // start clk
		CLK = 0;
		Di = 1;
		CLK = 1; // Signed ended
		CLK = 0;
		Di = 1;
		CLK = 1; // D2 Dont care din
		CLK = 0;
		Di = d1;
		CLK = 1; // user seleccted channel
		CLK = 0;
		Di = d0;
		CLK = 1; // usre selected channel
		CLK = 0;
		Di = 1;
		CLK = 1; // DC Sample clk
		CLK = 0;
		Di = 1;
		CLK = 1; // DC Stop Analog Sampling bit

		for (i = 11; i >= 0; i--)
		{
			CLK = 0;
			if (Do == 1)
				val |= (1 << i);
			CLK = 1;
		}

		lcd_cmd(0xc0);
		delay(4);
		CS = 1;
		if (ch != 3)
		{

			f = (float)(val * 5) / 4095;
			lcd_float(f);
			lcd_data('V');
			delay(100);
		}
		else if (ch == 3)
		{
			val = val / (40.95);
			lcd_int(val);
			lcd_data('%');
			delay(100);
		}

		val = 0;

		if (flag)
		{
			lcd_cmd(0x01);
			lcd_string("Stop");
			delay(1000);
			lcd_cmd(0x01);
			flag = 0;
			EA = ES = 0; // desable uart int
			break;
		}
	}

	uart_string("\r\n\r\nIs Sensor Output ShowUp Parfect (y/n)??\r\n");
jas:
	x = uart_rxd();
	if ((x == 'y') || (x == 'Y'))
	{
		uart_string("Press Enter/AnyKey For EXIT\r\nPress R To Check Another Chhannel\r\n");
		x = uart_rxd();
		if ((x == 'r') || (x == 'R'))
		{
			goto start_;
		}
		uart_string("\r\n");
		return;
	}
	else if ((x == 'N') || (x == 'n'))
	{
		uart_string("\r\nMakeSure\r\n1.Check Each Lag Of MCP3204 Proper\r\n2.Connection Of CLK,Dout,Din,CS Pins Is Proper\r\n3.Sensor Connected To Right Channel\r\n4.If Potentiometer Is Connected At Channel,Set It Zero First\r\nAgain ");
		goto start_;
	}
	else
	{
		uart_string("\r\nPlease Choose (y/n) Only\r\n");
		goto jas;
	}
}