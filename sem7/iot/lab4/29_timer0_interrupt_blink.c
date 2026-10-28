/* Timer0 interrupt blink: P1.0 toggles on each overflow. */
#include "lab4_common.h"

SBIT(LED, 0x90);

ISR(timer0_isr, 1)
{
    LED = !LED;
    TH0 = 0xFC;
    TL0 = 0x66;
}

void main(void)
{
    TMOD = (TMOD & 0xF0) | 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while(1);
}
