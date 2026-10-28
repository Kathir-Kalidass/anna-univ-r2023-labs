/* GSM terminal demonstration: sends AT then waits for/echoes response bytes. */
#include "lab4_common.h"
void main(void) { uart_init();uart_puts("AT\r\n");while(1)if(RI)uart_putc(uart_getc()); }
