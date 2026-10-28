/* Experiment 21 : Timer0 overflow counter - count overflows on P1
   Number of Timer0 overflows is shown in binary on Port 1. */
#include "mcu51.h"

unsigned char overflows = 0;

ISR(timer0_isr, 1)
{
    overflows++;             /* count each overflow  */
    P1 = overflows;          /* display count        */

    TH0 = 0xFC;              /* reload for 1 ms      */
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
