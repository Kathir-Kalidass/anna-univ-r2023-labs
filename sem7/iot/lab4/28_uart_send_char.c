/* Send one character repeatedly over UART at 9600 baud. */
#include "lab4_common.h"

void main(void)
{
    uart_init();

    while(1)
    {
        uart_putc('A');
        uart_putc('\r');
        uart_putc('\n');
        delay_ms(1000);
    }
}
