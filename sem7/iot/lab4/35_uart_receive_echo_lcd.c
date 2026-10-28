/* Receive a UART character, echo it, and show it on LCD. */
#include "lab4_common.h"

void main(void)
{
    unsigned char ch;

    uart_init();
    lcd_init();

    while(1)
    {
        ch = uart_getc();
        uart_putc(ch);
        lcd_cmd(0x80);
        lcd_puts("CH=");
        lcd_data(ch);
    }
}
