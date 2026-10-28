/* Counter mode: count external pulses on T0 and display on P1. */
#include "mcu51.h"

void main(void)
{
    TMOD = 0x05;   /* Timer0 counter mode 1 */
    TH0 = 0;
    TL0 = 0;
    TR0 = 1;

    while(1)
        P1 = TL0;
}
