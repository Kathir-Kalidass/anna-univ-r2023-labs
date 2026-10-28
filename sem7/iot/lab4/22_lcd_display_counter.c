/* LCD demo: show a counter value. */
#include "lab4_common.h"

void main(void)
{
    unsigned char count = 0;

    lcd_init();

    while(1)
    {
        lcd_cmd(0x80);
        lcd_puts("CNT=");
        lcd_u8(count);
        count++;
        delay_ms(250);
    }
}
