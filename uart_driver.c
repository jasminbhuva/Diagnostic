#include <reg51.h>
#include "header.h"
extern bit flag;
void uart_txd(unsigned char ch)
{
	SBUF = ch; // add(0x99)
	while (TI == 0)
		;	// checking till not ti flag becom 1
	TI = 0; // IMP dont forgot to clean
}

// void uart_init(unsigned int baud)
void uart_init(unsigned int baud)
{
	TMOD = 0x20;  // select Timer1 & mode2(auto relode)
	SCON = 0x50;  // select mode1(univesel),REN enable
	switch (baud) // baudrate by TH1(Timer Higher byte reg)
	{
	case 9600:
		TH1 = 253;
		break;
	case 7200:
		TH1 = 252;
		break;
	case 19200:
		TH1 = 253;
		PCON |= (1 << 7);
		break;
	case 28800:
		TH1 = 255;
		break;
	case 57600:
		TH1 = 255;
		PCON |= (1 << 7);
		break;
	default:
		TH1 = 253;
	}
	// TH1 = 253;
	TR1 = 1; // starting timer
}

unsigned char uart_rxd(void)
{
	while (RI == 0)
		;
	RI = 0;
	return SBUF;
}

void uart_string(char *p)
{
	while (*p)
	{
		// uart_txd(*p);
		SBUF = *p;
		while (TI == 0)
			;
		TI = 0;
		p++;
	}
}

// void uart_rxd_string(char *p,char max_ele)
//{
//	unsigned char i=0;
//	for(i=0;i<max_ele;i++)
//	{
//		while(RI==0);
//		RI=0;
//		p[i]=SBUF;
//		if(p[i]=='\r')
//			break;
//	}
//	p[i]=0;
// }

void uart_en(void)
{
	ES = EA = 1;
}

void uart_handler(void) interrupt 4
{
	if (RI == 1)
		RI = 0;
	else
		TI = 0;
	flag = 1;
}