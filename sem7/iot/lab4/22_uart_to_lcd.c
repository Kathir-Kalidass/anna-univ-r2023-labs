/* Type a character in terminal: it is displayed on LCD and echoed. */
#include "lab4_common.h"
void main(void) { unsigned char c; uart_init(); lcd_init(); lcd_puts("UART character:"); lcd_cmd(0xC0); while(1) { c=uart_getc(); lcd_data(c); uart_putc(c); } }
