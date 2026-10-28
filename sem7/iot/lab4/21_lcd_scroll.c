/* LCD text continuously scrolls left using command 18H. */
#include "lab4_common.h"
void main(void) { lcd_init(); lcd_puts("WELCOME TO 8051 LAB   "); while(1) { lcd_cmd(0x18); delay_ms(300); } }
