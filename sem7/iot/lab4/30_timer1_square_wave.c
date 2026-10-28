/* Timer1 square-wave generator using polling. */
#include "lab4_common.h"

SBIT(OUT, 0x90);

void wait_timer1_1ms(void)
{
    TMOD = (TMOD & 0x0F) | 0x10;
    TH1 = 0xFC;
    TL1 = 0x66;
    TF1 = 0;
    TR1 = 1;
    while(TF1 == 0);
    TR1 = 0;
    TF1 = 0;
}

void main(void)
{
    while(1)
    {
        OUT = !OUT;
        wait_timer1_1ms();
    }
}
