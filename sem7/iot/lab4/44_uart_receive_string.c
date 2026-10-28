/* Receive up to 15 characters; echo them and terminate on Enter. */
#include "lab4_common.h"
void main(void) { unsigned char c,n=0; uart_init();uart_puts("Enter text:\r\n");while(1){c=uart_getc();uart_putc(c);if(c=='\r'){uart_puts("\n");n=0;}else if(n<15)n++;} }
