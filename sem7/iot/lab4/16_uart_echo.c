/* Echo received UART characters back to the serial terminal. */
#include "lab4_common.h"

void main(void)
{
    uart_init();

    while(1)
    {
        uart_putc(uart_getc());
    }
}
