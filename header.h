#include <reg51.h>
void led_testing(void);

unsigned char menu_display(void);
void switch_testing(void);
void lcd_testing(void);
void lcd_check(void);
void keypad_testing(void);
void eeprom_testing(void);
void adc_testing(void);

void lcd_string(char *p);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_data(unsigned char d);
void lcd_int(int d);
void lcd_float(float d);

extern void uart_string(char *p);
extern void uart_rxd_string(char *p, char max_ele);
extern void uart_txd(unsigned char ch);
extern void uart_init(unsigned int baud);
// extern void uart_init(void);
extern unsigned char uart_rxd(void);
void uart_en(void); // uart interrupt

int i2c_byte_read(unsigned char SA, unsigned char MA);
void i2c_byte_write(unsigned char SA, unsigned char MA, unsigned char d);
void i2c_nack(void);
unsigned char i2c_read(void);
void i2c_write(unsigned char d);
bit i2c_ack(void);
void i2c_stop(void);
void i2c_start(void);

extern void delay(int ms);