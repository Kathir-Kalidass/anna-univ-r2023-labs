/* Experiment 43 : Two digit counter display (application)
   Counts 00-99 on button press (INT0 = P3.2).
   Tens digit on P1 (upper nibble = BCD tens)
   Units digit on P0 (lower nibble = BCD units)
   To test: press INT0 in simulator, watch P1/P0. */
#include "mcu51.h"

unsigned char units = 0;
unsigned char tens  = 0;

ISR(ext0_isr, 0)
{
    units++;

    if(units == 10)        /* carry to tens */
    {
        units = 0;
        tens++;
    }
    if(tens == 10)         /* wrap at 99 */
        tens = 0;

    P0 = (P0 & 0xF0) | units;   /* units digit on low nibble  */
    P1 = (P1 & 0x0F) | (tens << 4); /* tens digit high nibble */
}

void main(void)
{
    EA  = 1;
    EX0 = 1;
    IT0 = 1;

    while(1);
}
