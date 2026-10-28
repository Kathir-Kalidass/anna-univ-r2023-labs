/* Timer0 polling delay template. Output: P1.0 toggles with a visible delay. */
#include "lab4_common.h"

SBIT(LED, 0x90);

void timer0_delay_1ms(void)
{
    TMOD = (TMOD & 0xF0) | 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    TF0 = 0;
    TR0 = 1;
    while(TF0 == 0);
    TR0 = 0;
    TF0 = 0;
}

void timer_delay_ms(unsigned int ms)
{
    while(ms--)
        timer0_delay_1ms();
}

void main(void)
{
    LED = 1;

    while(1)
    {
        LED = !LED;
        timer_delay_ms(500);
    }
}
