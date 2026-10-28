/* Integrated demo: P0 mirrors to P1; sends and displays elapsed seconds. */
#include "lab4_common.h"
void main(void) { unsigned char sec=0; P0=0xFF; uart_init(); lcd_init(); lcd_puts("Seconds:"); while(1) { P1=P0; delay_ms(1000); ++sec; lcd_cmd(0xC0); lcd_u8(sec); uart_puts("Second "); uart_putc((sec/10)+'0'); uart_putc((sec%10)+'0'); uart_puts("\r\n"); } }
