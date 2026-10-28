/* LCD demo: show switch state on the first line. */
#include "lab4_common.h"

SBIT(SW, 0xB2);

void main(void)
{
    lcd_init();

    while(1)
    {
        lcd_cmd(0x80);
        lcd_puts("SW=");
        lcd_data((SW == 0) ? '0' : '1');
        lcd_puts(" ");
        delay_ms(100);
    }
}
