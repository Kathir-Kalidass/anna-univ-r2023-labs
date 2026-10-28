/* P0.0/P0.1 active-low choose LED or UART menu item. */
#include "lab4_common.h"
SBIT(NEXT,0x80); SBIT(SELECT,0x81);
void main(void) { unsigned char item=0; P0=0xFF; lcd_init(); while(1){lcd_cmd(0x80);lcd_puts(item?"2.UART TEST     ":"1.LED TEST      "); if(!NEXT){item=!item;while(!NEXT);} if(!SELECT){lcd_cmd(0xC0);lcd_puts(item?"UART selected   ":"LED selected    ");while(!SELECT);} } }
