/* LCD scroll text demo. */
#include "lab4_common.h"

void main(void)
{
    lcd_init();
    lcd_cmd(0x80);
    lcd_puts("WELCOME TO 8051");

    while(1)
    {
        lcd_cmd(0x18);   /* shift display left */
        delay_ms(300);
    }
}
