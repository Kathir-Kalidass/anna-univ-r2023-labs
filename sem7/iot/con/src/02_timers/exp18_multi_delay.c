/* Experiment 18 : Multiple delays using Timer0 (5 ms, 20 ms, 50 ms)
   Blink sequence : LED on 50 ms, off 20 ms, on 5 ms, off 20 ms. */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

void timer_delay(unsigned int ms)
{
    unsigned int k;

    for(k = 0; k < ms; k++)      /* repeat ms times */
    {
        TMOD = 0x01;             /* Timer0 Mode 1 */

        TH0 = 0xFC;
        TL0 = 0x66;              /* ~1 ms load */

        TR0 = 1;

        while(TF0 == 0);         /* wait for overflow */

        TR0 = 0;
        TF0 = 0;
    }
}

void main(void)
{
    while(1)
    {
        LED = 0;   timer_delay(50);   /* ON  50 ms  */
        LED = 1;   timer_delay(20);   /* OFF 20 ms  */
        LED = 0;   timer_delay(5);    /* ON   5 ms  */
        LED = 1;   timer_delay(20);   /* OFF 20 ms  */
    }
}
