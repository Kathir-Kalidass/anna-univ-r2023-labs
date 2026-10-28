/* Experiment 14 : Timer0 based delay (polling) - Blink LED
   Timer0 Mode 1 (16-bit).  TH0/TL0 = 0xFC66 -> ~1 ms at 12 MHz. */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

void delay_1ms(void)
{
    TMOD = 0x01;     /* Timer0, Mode 1 (16-bit) */

    TH0 = 0xFC;
    TL0 = 0x66;      /* load count for ~1 ms */

    TR0 = 1;         /* start Timer0 */

    while(TF0 == 0); /* wait for overflow flag */

    TR0 = 0;         /* stop timer  */
    TF0 = 0;         /* clear flag  */
}

void main(void)
{
    while(1)
    {
        LED = !LED;
        delay_1ms();
    }
}
