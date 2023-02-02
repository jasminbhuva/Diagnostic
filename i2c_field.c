/* i2c_field */
#include "header.h"
void delay(int ms);

sbit SCL = P3 ^ 2;
sbit SDA = P3 ^ 3;

void i2c_start(void)
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
}

void i2c_stop(void)
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

bit i2c_ack(void)
{
	SCL = 0;
	SDA = 1;
	SCL = 1;
	delay(10);
	if (SDA == 0)
	{
		SCL = 0;
		return 0;
	}
	else
	{
		SCL = 0;
		return 1;
	}
}

void i2c_write(unsigned char d)
{
	char i;
	for (i = 7; i >= 0; i--)
	{
		SCL = 0;
		SDA = (d >> i) & 1;
		SCL = 1;
	}
}

unsigned char i2c_read(void)
{
	unsigned char temp = 0;
	char i;
	for (i = 7; i >= 0; i--)
	{
		SCL = 1;
		if (SDA == 1)
			temp |= (1 << i);
		SCL = 0;
	}
	return temp;
}

void i2c_nack(void)
{
	SCL = 0;
	SDA = 1;
	SCL = 1;
}

void i2c_byte_write(unsigned char SA, unsigned char MA, unsigned char d)
{
	bit r;

	i2c_start();

	i2c_write(SA);

	r = i2c_ack();
	if (r == 1)
		goto check;

	i2c_write(MA);

	r = i2c_ack();
	if (r == 1)
		goto check;

	i2c_write(d);

	r = i2c_ack();
	if (r == 1)
		goto check;

check:
	i2c_stop();
}

int i2c_byte_read(unsigned char SA, unsigned char MA)
{

	bit r;

	int temp = -1;
	i2c_start();
	i2c_write(SA);

	r = i2c_ack();
	if (r == 1)
		goto stop;

	i2c_write(MA);
	r = i2c_ack();
	if (r == 1)
		goto stop;

	i2c_start();

	i2c_write(SA | 1); // Slave add with read instruction
	r = i2c_ack();
	if (r == 1)
		goto stop;

	temp = i2c_read();
	i2c_nack();

stop:
	i2c_stop();

	return temp;
}