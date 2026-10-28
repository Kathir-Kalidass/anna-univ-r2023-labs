/* Experiment 22 : Interrupt counter - count INT0 (P3.2) presses on P1 */
#include "mcu51.h"

unsigned char count = 0;

ISR(ext0_isr, 0)
{
    count++;
    P1 = count;   /* show count in binary */
}

void main(void)
{
    EA  = 1;
    EX0 = 1;
    IT0 = 1;      /* falling edge triggered */

    while(1);
}
