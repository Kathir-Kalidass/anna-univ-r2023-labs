/* UART command control: 1 = LED ON, 0 = LED OFF, T = toggle. */
#include "lab4_common.h"

SBIT(LED, 0x90);

void main(void)
{
    unsigned char ch;

    uart_init();
    LED = 1;

    while(1)
    {
        ch = uart_getc();

        if(ch == '1')
            LED = 0;
        else if(ch == '0')
            LED = 1;
        else if(ch == 'T' || ch == 't')
            LED = !LED;

        uart_putc(ch);
    }
}
