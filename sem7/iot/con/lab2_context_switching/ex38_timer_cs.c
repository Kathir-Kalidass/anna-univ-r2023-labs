/* Lab-2 Activities Ex8 : Timer-based CONTEXT SWITCHING
   Timer0 interrupt periodically saves the running task context
   and restores the next task context (round-robin).
   Task1 : LED blinking on P1.0.
   Task2 : counter increment shown on P0.
   Task3 : port monitoring (P3.2 -> P2.0). */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 */
SBIT(SW,   0xB2);          /* P3.2 */
SBIT(SWLed, 0xA0);         /* P2.0 */

unsigned char current  = 0;
unsigned char blinkCtr = 0;
unsigned char counter  = 0;

void TaskLedBlink(void)
{
    blinkCtr++;
    if(blinkCtr >= 100)
    {
        blinkCtr = 0;
        LED1 = (LED1 == 0) ? 1 : 0;
    }
}

void TaskCounter(void)
{
    P0 = counter;
    counter++;
}

void TaskPortMonitor(void)
{
    if(SW == 0)
        SWLed = 0;
    else
        SWLed = 1;
}

ISR(Timer0ISR, 1)              /* every 5 ms */
{
    TH0 = 0xEC;
    TL0 = 0x78;
    current = (current + 1) % 3;   /* round-robin context switch */
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskLedBlink();    break;
        case 1: TaskCounter();     break;
        case 2: TaskPortMonitor(); break;
    }
}

void main(void)
{
    TMOD = 0x01;               /* Timer0 mode 1, 16-bit */
    TH0 = 0xEC; TL0 = 0x78;
    ET0 = 1;                   /* enable Timer0 interrupt */
    EA  = 1;
    TR0 = 1;                   /* start timer */

    while(1)
    {
        Scheduler();           /* run the current task */
    }
}
