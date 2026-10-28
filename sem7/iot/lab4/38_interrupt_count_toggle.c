/* Count INT0 interrupts and show the count on P1. */
#include "mcu51.h"

unsigned char count = 0;

ISR(ext0_isr, 0)
{
    count++;
    P1 = count;
}

void main(void)
{
    EA = 1;
    EX0 = 1;
    IT0 = 1;

    while(1);
}
