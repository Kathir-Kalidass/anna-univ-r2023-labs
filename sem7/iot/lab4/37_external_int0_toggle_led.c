/* INT0 on P3.2 toggles LED on P1.0. */
#include "lab4_common.h"

SBIT(LED, 0x90);

ISR(ext0_isr, 0)
{
    LED = !LED;
}

void main(void)
{
    EA = 1;
    EX0 = 1;
    IT0 = 1;

    while(1);
}
