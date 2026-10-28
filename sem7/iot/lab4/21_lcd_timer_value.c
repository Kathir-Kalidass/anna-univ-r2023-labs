/* LCD demo: display a software seconds counter. */
#include "lab4_common.h"

void main(void)
{
    unsigned char seconds = 0;

    lcd_init();

    while(1)
    {
        lcd_cmd(0x80);
        lcd_puts("SEC=");
        lcd_u8(seconds);

        delay_ms(1000);
        seconds++;
    }
}
