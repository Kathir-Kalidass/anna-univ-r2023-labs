/* Timer0 interrupt based context switching between two tasks. */
#include "mcu51.h"

unsigned char task = 0;

ISR(timer0_isr, 1)
{
    if(task == 0)
    {
        P1 = 0x55;
        task = 1;
    }
    else
    {
        P1 = 0xAA;
        task = 0;
    }

    TH0 = 0xFC;
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA  = 1;
    TR0 = 1;

    while(1);
}
