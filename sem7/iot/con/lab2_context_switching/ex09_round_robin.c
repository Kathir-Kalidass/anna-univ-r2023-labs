/* Lab-2 Ex9 : Round-Robin scheduler using CONTEXT SWITCHING
   Task0 : running LED pattern on P1.
   Task1 : read switch P3.2 -> LED P2.0.
   Task2 : counter incremented and shown on P0.
   A round-robin scheduler gives each task a time slice; the
   "context" of every task (its counters, outputs) is kept in
   shared variables that are saved/restored on each switch. */
#include "mcu51.h"

SBIT(SW,   0xB2);          /* P3.2 input switch  */
SBIT(SWLed, 0xA0);         /* P2.0 output LED    */

unsigned char pattern = 0x01;
unsigned char counter = 0;
unsigned char current = 0;

void TaskLedPattern(void)
{
    P1 = pattern;
    pattern = (pattern << 1);
    if(pattern == 0)
        pattern = 0x01;             /* shift the single bit round */
}

void TaskSwitch(void)
{
    if(SW == 0)
        SWLed = 0;                  /* switch pressed -> LED on   */
    else
        SWLed = 1;
}

void TaskCounter(void)
{
    P0 = counter;                   /* show counter on P0 */
    counter++;
}

void Scheduler(void)                 /* round-robin context switch */
{
    current = (current + 1) % 3;

    switch(current)
    {
        case 0: TaskLedPattern(); break;
        case 1: TaskSwitch();     break;
        case 2: TaskCounter();    break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
