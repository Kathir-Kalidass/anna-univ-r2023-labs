/* Change the text below to your own roll number. */
#include "lab4_common.h"
void main(void) { lcd_init(); lcd_puts("ROLL NUMBER"); lcd_cmd(0xC0); lcd_puts("YOUR-ROLL-NO"); while(1); }
