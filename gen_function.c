#include "header.h"
#include <reg51.h>
sbit SWITCH = P2 ^ 3;
sbit LED1 = P2 ^ 4;
sbit LED2 = P2 ^ 5;
sbit LED3 = P2 ^ 6;
sbit LED4 = P2 ^ 7;

sbit R0 = P1 ^ 4;
sbit R1 = P1 ^ 5;
sbit R2 = P1 ^ 6;
sbit R3 = P1 ^ 7;
sbit C0 = P1 ^ 0;
sbit C1 = P1 ^ 1;
sbit C2 = P1 ^ 2;
sbit C3 = P1 ^ 3;
unsigned char i, x;

// function for DISPLAY MENU
unsigned char menu_display(void) // display and choose option function
{

	uart_string("\t\tVector Board Dignosis -JASMIN.BHUVA\r\nA/a.LED Testing\r\nB/b.SWITCH Testing\r\nC/c.LCD Testing\r\nD/d.KEYPAD Testing\r\nE/e.I2C EEPROM Testing\r\nF/f.SPI ADC Testing\r\nEnter Option:-");
	x = uart_rxd();
	return x;
}

// fun for LED testing
void led_testing(void) // function of led testing
{

	uart_string("\r\n\r\nPlease Connect:\r\nActiv Low LEDS On P2.4 To P2.7(4 Leds)\r\nPRESS Enter To Check"); // whenever led testing start this msg will print
abc:
	x = uart_rxd(); // nothing but and taking input from S.T.
	LED1 = LED2 = LED3 = LED4 = 1;
	if (x == '\r') // '\r'is nothing but and ENTER_KEY
	{
		uart_string("\r\nTesting Is Start..\r\n");

		for (i = 0; i < 6; i++)
		{
			LED1 = ~LED1;
			delay(100);
			LED2 = ~LED2;
			delay(100);
			LED3 = ~LED3;
			delay(100);
			LED4 = ~LED4;
			delay(100);
		}
		LED1 = LED2 = LED3 = LED4 = 1;
		uart_string("\r\nAll LEDs Are Working (y/n) ??"); // after led stop this msg will prt on S.T.
	new_:
		x = uart_rxd();
		// x input action
		if ((x == 'n') || (x == 'N'))
		{
			uart_string("\r\n\r\nMake Sure\r\n1.Wire Connection Is Proper\r\n2.All LEDs Anodes Should Be Connected With VCC(+5vDC)\r\n3.All LEDs Cathodes Should Be Connected With P2.4-P2.7\r\nPRESS Enter To Test Again");
			goto abc;
		}
		else if ((x == 'y') || (x == 'Y'))
			goto back;
		else
		{
			uart_string("\r\nPlease Enter (y/n) Only:");
			goto new_;
		}
		// x input action
	back:
		uart_string("\r\n\r\nNow Connect:\r\nActive High LEDs On P2.4 to P2.7(4 Leds)\r\nPress Enter To Check:");
	back_:
		x = uart_rxd();
		LED1 = LED2 = LED3 = LED4 = 0;
		delay(100);
		if (x == '\r')
		{
			uart_string("\r\nTesting Is Start..\r\n");

			for (i = 0; i < 6; i++)
			{
				LED1 = ~LED1;
				delay(100);
				LED2 = ~LED2;
				delay(100);
				LED3 = ~LED3;
				delay(100);
				LED4 = ~LED4;
				delay(100);
			}
			LED1 = LED2 = LED3 = LED4 = 0;
		}
		else
		{
			uart_string("\r\nPlease Press ENTER Only:");
			goto back_;
		}

		uart_string("\r\nLED Working (y/n) ??"); // after led stop this msg will prt on S.T.
	xyz:
		x = uart_rxd();

		if ((x == 'y') || (x == 'Y')) // here x is y/Y
		{
			uart_string("\n\r\n\r");
			return;
		}
		else if ((x == 'N') || (x == 'n')) // here x is n/N
		{
			uart_string("\r\n\r\nMake Sure\r\n1.Wire Connection Is Proper\r\n2.LEDs Anodes Should Be Connected With P2.4 to P2.7\r\n3.LED Cathode Should Be Connected With VCC(+5v)\r\nPRESS Enter To Test Again");
			goto back_;
		}
		else
		{
			uart_string("\r\nPlease Enter (y/n) Only:");
			goto xyz;
		}
	}
	else
	{
		uart_string("\r\nPlease Press Enter Only\r\n");
		goto abc;
	}
}

////////////////// fun for SWITCH testing /////////////////////////////

void switch_testing(void)
{
	LED1 = 1;
	uart_string("\r\n\r\nPlease Connect:\r\nSwitch To P2.3\r\nLED To P2.4(Active Low Preferable)\r\nNow PRESS Switch 3 Time(With Delay Of 0.5 Sec)\r\n");
abc:

	for (i = 0; i < 3; i++)
	{
		while (SWITCH == 1)
			;

		LED1 = ~LED1;
		delay(250);
		while (SWITCH == 0)
			;
		// for deal with key bounceing
		LED1 = ~LED1;
		delay(250);
	}

	uart_string("\r\nIs LED Glow When Switch Pressed (y/n) ??");
xyz:
	x = uart_rxd(); // waiting from I/p From S.T.

	if ((x == 'y') || (x == 'Y'))
	{
		uart_string("\r\n\r\n");
		return;
	}
	else if ((x == 'N') || (x == 'n')) // here x is 2.NO
	{
		uart_string("\r\n\r\nMake Sure\r\n1.Wire Connection Is Proper\r\n2.Switch Second Terminal Connected With GND\r\n3.LED Connected Proprly\r\nNow PRESS Switch 3 Time(With Delay Of 0.5 Sec)\r\n");
		goto abc;
	}
	else
	{
		uart_string("\r\nPlease Enter (y/n) Only!\r\n");
		goto xyz;
	}
}

///////////////  fun for LCD testing ///////////////////////
void lcd_testing(void)
{
	uart_string("\r\n\r\nPlease Connect:\r\nLCD D0-D7 T0 P0-P7\r\nRS To P2.0\r\nRW To P2.1\r\nEN To P2.2\r\nPress Enter To Check");
abc:
	x = uart_rxd();

	if (x == '\r')
	{
		uart_string("\r\nStart Testing...\r\n");
		lcd_check();
	}
	else
	{
		uart_string("\r\nPlease Press Enter Only\r\n");
		goto abc;
	}
xyz:
	uart_string("\r\nIs Every Words & Pixel Of LCD Working (y/n) ??");
	//	for(i=0;i<10;i++)
	x = uart_rxd();

	if ((x == 'y') || (x == 'Y'))
	{
		uart_string("\r\n\r\n");
		return;
	}
	else if ((x == 'n') || (x == 'N'))
	{
		uart_string("\r\n\r\nMake Sure\r\n1.RS At P2.0 Connect\r\n2.RW At p2.1 Connect\r\n3.EN At p2.2 Connected\r\n4.LCD Is In 8-Bit Mode So\r\n  D0-D7 Pins Should Be Connected To P0.0-P0.7\r\n5.Port0 Need Pull_Up Reg\r\n  Connect If Not Connected\r\nPRESS Enter To Check Again");
		goto abc;
	}
	else // if (((x!='n')&&(x!='N'))&&((x!='Y')&&(x!='y')))
		goto xyz;
}

///////////// Keypad testing(4x4) ///////////////////////

void keypad_testing(void)
{

	unsigned char row = 0, col = 0;

	code unsigned char ary[4][4] = {{'1', '5', '9', 'D'},
									{'2', '6', 'A', 'E'},
									{'3', '7', 'B', 'F'},
									{'4', '8', 'C', '='}};

	uart_string("\r\n\r\nConnect 4x4 KeyPad:");
abc:
	uart_string("\r\nP1.0-P1.3 To C0-C3\r\nP1.4-P1.7 To R0-R3\r\nAfter Press All Switch Last Press [4][4] (SW16) To Exit\r\n");
	uart_string("\r\nStart Testing...\r\n");

	while (1)
	{

		R0 = R1 = R3 = R2 = 0;
		C0 = C1 = C2 = C3 = 1;

		while ((C1 & C2 & C3 & C0) != 0)
			;
		R0 = 0;
		R1 = R3 = R2 = 1;
		if ((C0 & C1 & C2 & C3) == 0)
		{
			row = 0;
			goto col_check;
		}
		R1 = 0;
		R0 = R3 = R2 = 1;
		if ((C0 & C1 & C2 & C3) == 0)
		{
			row = 1;
			goto col_check;
		}
		R2 = 0;
		R0 = R1 = R3 = 1;
		if ((C0 & C1 & C2 & C3) == 0)
		{
			row = 2;
			goto col_check;
		}
		R3 = 0;
		R0 = R1 = R2 = 1;
		if ((C0 & C1 & C2 & C3) == 0)
		{
			row = 3;
			goto col_check;
		}
	col_check:
		if (C0 == 0)
			col = 0;
		else if (C1 == 0)
			col = 1;
		else if (C2 == 0)
			col = 2;
		else
			col = 3;
		if ((ary[col][row]) == '=')
		{
			RI = 0;
			TI = 0;
			x = 0;
			uart_string("\r\nAll Switch Work Proper(y/n)??\r\n");
		abc_:
			x = uart_rxd();

			if ((x == 'y') || (x == 'Y'))
			{
				uart_string("\r\n");
				break;
			}
			else if ((x == 'n') || (x == 'N'))
			{
				uart_string("\r\nMakeSure\r\n1.Every Connection Is Proper\r\n2.Press Switch One By One (with delay of 0.5 sec)\r\n3.All Connection And Again Connect To");
				goto abc;
			}
			else
			{
				uart_string("\r\nPlease Enter (y/n) Only!!\r\n");
				goto abc_;
			}
		}
		while ((C1 & C2 & C0 & C3) == 0)
			;

		delay(500);
		uart_txd(ary[col][row]);

	} // while
} // end
