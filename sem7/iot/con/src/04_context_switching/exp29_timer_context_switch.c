/* Experiment 29 : Context switching using TIMER0 interrupt
   Timer0 overflow -> ISR (acts as scheduler) switches Task1/Task2.
   Output : P1 alternates 0x55 <-> 0xAA on every overflow. */
#include "mcu51.h"

unsigned char task = 0;

ISR(timer0_isr, 1)
{
    /* --- context switch happens here ---------------------- */
    if(task == 0)
    {
        P1 = 0x55;     /* run Task1  */
        task = 1;      /* next: Task2 */
    }
    else
    {
        P1 = 0xAA;     /* run Task2  */
        task = 0;      /* next: Task1 */
    }

    TH0 = 0xFC;        /* reload timer for next tick */
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;       /* Timer0 Mode 1 (16-bit) */

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;           /* enable Timer0 interrupt */
    EA  = 1;           /* enable global interrupt */

    TR0 = 1;           /* start Timer0 */

    while(1);          /* CPU is free here - scheduler does the job */
}
