/* LCD demo: print HELLO on the first line. */
#include "lab4_common.h"

void main(void)
{
    lcd_init();
    lcd_cmd(0x80);
    lcd_puts("HELLO");

    while(1);
}
