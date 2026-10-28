/* Experiment 17 : Square wave generation on P1.0 using Timer0 interrupt
   Each overflow toggles the output -> 50% duty cycle square wave. */
#include "mcu51.h"

SBIT(OUT, 0x90);   /* P1.0 */

ISR(timer0_isr, 1)
{
    OUT = !OUT;      /* toggle -> one half period per overflow */

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
