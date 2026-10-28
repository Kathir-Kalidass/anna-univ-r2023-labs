/* Type in serial terminal: each received character is echoed. */
#include "lab4_common.h"
void main(void) { unsigned char c; uart_init(); uart_puts("Echo ready\r\n"); while(1) { c=uart_getc(); uart_putc(c); } }
