/* Serial output @9600: HELLO every second. */
#include "lab4_common.h"
void main(void) { uart_init(); while(1) { uart_puts("HELLO\r\n"); delay_ms(1000); } }
