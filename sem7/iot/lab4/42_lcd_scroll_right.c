/* LCD text scrolls right using command 1CH. */
#include "lab4_common.h"
void main(void) { lcd_init(); lcd_puts("8051 MCU IDE"); while(1){lcd_cmd(0x1C);delay_ms(300);} }
