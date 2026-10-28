/* Simple traffic-light sequence using software delay loops. */
#include "lab4_common.h"

SBIT(RED,    0x90);
SBIT(YELLOW, 0x91);
SBIT(GREEN,  0x92);

void main(void)
{
    while(1)
    {
        RED = 0;
        YELLOW = 1;
        GREEN = 1;
        delay_ms(5000);

        RED = 1;
        YELLOW = 0;
        GREEN = 1;
        delay_ms(1000);

        RED = 1;
        YELLOW = 1;
        GREEN = 0;
        delay_ms(4000);
    }
}
