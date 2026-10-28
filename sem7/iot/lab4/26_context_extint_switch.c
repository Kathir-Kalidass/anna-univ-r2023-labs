/* INT0 based context switching between two tasks. */
#include "mcu51.h"

unsigned char task = 0;

ISR(ext0_isr, 0)
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
}

void main(void)
{
    EA = 1;
    EX0 = 1;
    IT0 = 1;

    while(1);
}
