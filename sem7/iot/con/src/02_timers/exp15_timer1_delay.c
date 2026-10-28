/* Experiment 15 : Timer1 based delay (polling) - Blink LED
   Timer1 Mode 1 (16-bit).  TMOD = 0x10 selects Timer1 mode1. */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

void delay_1ms_timer1(void)
{
    TMOD = 0x10;     /* Timer1, Mode 1 (16-bit) */

    TH1 = 0xFC;
    TL1 = 0x66;

    TR1 = 1;         /* start Timer1 */

    while(TF1 == 0); /* wait for overflow */

    TR1 = 0;
    TF1 = 0;
}

void main(void)
{
    while(1)
    {
        LED = !LED;
        delay_1ms_timer1();
    }
}
