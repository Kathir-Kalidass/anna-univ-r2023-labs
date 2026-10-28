/* LCD demo: show a received UART character. */
#include "lab4_common.h"

void main(void)
{
    unsigned char ch;

    uart_init();
    lcd_init();

    while(1)
    {
        ch = uart_getc();
        lcd_cmd(0x80);
        lcd_puts("RX=");
        lcd_data(ch);
        uart_putc(ch);
    }
}
