/* Shared helpers.  Crystal: 11.0592 MHz.  LCD: P2=D0..D7, RS=P3.4, EN=P3.5,
   RW grounded. UART retains P3.0/RXD and P3.1/TXD. */
#ifndef LAB4_COMMON_H
#define LAB4_COMMON_H
#include "mcu51.h"
SBIT(LCD_RS, 0xB4);
SBIT(LCD_EN, 0xB5);

void delay_ms(unsigned int ms) {
    unsigned int a, b;
    while (ms--) for (a = 0; a < 8; a++) for (b = 0; b < 127; b++);
}
void uart_init(void) {
    TMOD = (TMOD & 0x0F) | 0x20; /* Timer1 mode 2 */
    TH1 = 0xFD; TL1 = 0xFD;      /* 9600 baud @ 11.0592 MHz */
    SCON = 0x50; TI = 0; RI = 0; TR1 = 1;
}
void uart_putc(unsigned char c) { SBUF = c; while (!TI); TI = 0; }
void uart_puts(const char *s) { while (*s) uart_putc(*s++); }
unsigned char uart_getc(void) { while (!RI); RI = 0; return SBUF; }
void lcd_pulse(void) { LCD_EN = 1; delay_ms(1); LCD_EN = 0; delay_ms(1); }
void lcd_cmd(unsigned char c) { LCD_RS = 0; P2 = c; lcd_pulse(); }
void lcd_data(unsigned char c) { LCD_RS = 1; P2 = c; lcd_pulse(); }
void lcd_init(void) { delay_ms(20); lcd_cmd(0x38); lcd_cmd(0x0C); lcd_cmd(0x06); lcd_cmd(0x01); }
void lcd_puts(const char *s) { while (*s) lcd_data(*s++); }
void lcd_u8(unsigned char value) {
    lcd_data((value / 100) + '0'); lcd_data(((value / 10) % 10) + '0'); lcd_data((value % 10) + '0');
}
void timer0_50ms(void) { /* Mode 1 reload FC66: 50 ms */
    TMOD = (TMOD & 0xF0) | 0x01; TH0 = 0x4C; TL0 = 0x00; TF0 = 0; TR0 = 1;
    while (!TF0); TR0 = 0; TF0 = 0;
}
void timer0_ms(unsigned char n) { while (n--) { TMOD = (TMOD & 0xF0) | 0x01; TH0=0xFC; TL0=0x66; TF0=0; TR0=1; while(!TF0); TR0=0; TF0=0; } }
#endif
