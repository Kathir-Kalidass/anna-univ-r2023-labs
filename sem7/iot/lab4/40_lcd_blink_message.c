/* LCD message blinks using display ON/OFF commands. */
#include "lab4_common.h"
void main(void) { lcd_init(); lcd_puts("WELCOME"); while(1){lcd_cmd(0x08);delay_ms(500);lcd_cmd(0x0C);delay_ms(500);} }
