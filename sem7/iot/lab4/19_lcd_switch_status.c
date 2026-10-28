/* P0.0 active-low switch status appears on the LCD. */
#include "lab4_common.h"
SBIT(SW,0x80);
void main(void) { P0=0xFF; lcd_init(); lcd_puts("Switch status:"); while(1) { lcd_cmd(0xC0); if(!SW) lcd_puts("PRESSED "); else lcd_puts("RELEASED"); delay_ms(100); } }
