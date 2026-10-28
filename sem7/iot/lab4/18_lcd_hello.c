/* LCD output line 1: HELLO; line 2: 8051 LAB. */
#include "lab4_common.h"
void main(void) { lcd_init(); lcd_puts("HELLO"); lcd_cmd(0xC0); lcd_puts("8051 LAB"); while(1); }
