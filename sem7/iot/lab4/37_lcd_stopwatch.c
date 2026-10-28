/* LCD stopwatch counts seconds 000..255. */
#include "lab4_common.h"
void main(void) { unsigned char sec=0; lcd_init(); lcd_puts("Stopwatch:"); while(1){lcd_cmd(0xC0);lcd_u8(sec++);delay_ms(1000);} }
