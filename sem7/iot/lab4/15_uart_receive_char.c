/* Receive one character over UART and show it on P1. */
#include "lab4_common.h"

void main(void)
{
    unsigned char ch;

    uart_init();

    while(1)
    {
        ch = uart_getc();
        P1 = ch;
        uart_putc(ch);
    }
}
