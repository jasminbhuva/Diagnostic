#include <reg51.h>
#include "header.h"
// char i;
sbit RS = P2 ^ 0;
sbit RW = P2 ^ 1;
sbit EN = P2 ^ 2;

/* delay */

void delay(int ms)
{
	unsigned char i;
	for (; ms > 0; ms--)
	{
		for (i = 250; i > 0; i--)
			;

		for (i = 247; i > 0; i--)
			;
	}
}
/* LCD DRIVER */
void lcd_cmd(unsigned char cmd)
{
	P0 = cmd;
	RS = 0;
	RW = 0;
	EN = 1;
	delay(5);
	EN = 0;
}
void lcd_init(void)
{
	EN = 0;
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x0e);
}

void lcd_data(unsigned char d)
{
	P0 = d;
	RS = 1;
	RW = 0;
	EN = 1;
	delay(5);
	EN = 0;
}
void lcd_string(char *p)
{
	while (*p)
	{
		lcd_data(*p);
		p++;
	}
}

void lcd_check(void)
{
	char i, j;
	// char j;
	code char ary[] = "LCD_CHECKING";

	lcd_cmd(0x0c);
	for (i = 15; i >= 0; i--) // print till string reach 0x80 add
	{
		lcd_cmd(0xc0 + i); // start printing from last notch of display
		lcd_string(ary);
		delay(50);
		lcd_cmd(0x01);
	}
	for (i = 1; i < 17; i++)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x90 - i); // start from last notch of 1st row
		for (j = 0; j < i; j++)
		{
			if (j < 13) // printf till length of string
				lcd_data(ary[j]);
		}
		if (i < 12) // this is for 2nd row
		{
			lcd_cmd(0xc0);
			lcd_string(ary + i); //
		}
	}
	for (i = 1; i < 13; i++) // statting from 0x80
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string(ary + i); // cut one by one char
		delay(50);
	}
}

void lcd_int(int d)
{
	unsigned char ary[5];
	char i = 0;
	if (d == 0)
	{
		lcd_data('0');
		lcd_data('.');
		lcd_data('0');
		lcd_data('0');
		return;
	}
	if (d < 0)
	{
		d = -d;
		lcd_data('-');
	}

	ary[1] = d % 10;
	d = d / 10;
	ary[0] = d;

	lcd_data(ary[0] + 48);
	lcd_data(ary[1] + 48);
}

void lcd_float(float d)
{

	char ary[4], i = 0;
	int x = d;
	float temp = d - x;
	if (d == 0)
	{
		lcd_data('0');
		lcd_data('.');
		lcd_data('0');
		lcd_data('0');
		return;
	}
	while (x)
	{
		ary[i++] = (x % 10) + 48;
		x = x / 10;
	}
	x = temp * 100;
	if (i == 0)
		ary[i++] = '0';
	ary[i] = '.';
	ary[++i] = (x / 10) + 48;
	ary[++i] = (x % 10) + 48;

	lcd_data(ary[0]);
	lcd_data(ary[1]);
	lcd_data(ary[2]);
	lcd_data(ary[3]);
}
