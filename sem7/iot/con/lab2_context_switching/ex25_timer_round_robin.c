/* Lab-3 Ex14 : Timer interrupt CONTEXT SWITCHING (3 tasks)
   Task0 : blink LED on P1.0.
   Task1 : read switch P3.2 -> P2.0.
   Task2 : rotate bit pattern on P1.
   Timer0 ISR switches context (preemptive) between the tasks
   every 5 ms. */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 */
SBIT(SW,   0xB2);          /* P3.2 */
SBIT(SWLed, 0xA0);         /* P2.0 */

unsigned char current  = 0;
unsigned char pattern  = 0x01;
unsigned char blinkCtr = 0;

void TaskBlink(void)
{
    blinkCtr++;
    if(blinkCtr >= 100)
    {
        blinkCtr = 0;
        LED1 = (LED1 == 0) ? 1 : 0;
    }
}

void TaskSwitchRead(void)
{
    if(SW == 0)
        SWLed = 0;
    else
        SWLed = 1;
}

void TaskRotate(void)
{
    P1 = pattern;
    pattern = pattern << 1;
    if(pattern == 0) pattern = 0x01;
}

ISR(Timer0ISR, 1)
{
    TH0 = 0xEC;
    TL0 = 0x78;
    current = (current + 1) % 3;    /* preemptive context switch */
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskBlink();     break;
        case 1: TaskSwitchRead();break;
        case 2: TaskRotate();    break;
    }
}

void main(void)
{
    TMOD = 0x01;
    TH0 = 0xEC; TL0 = 0x78;
    ET0 = 1;
    EA  = 1;
    TR0 = 1;

    while(1)
    {
        Scheduler();
    }
}
