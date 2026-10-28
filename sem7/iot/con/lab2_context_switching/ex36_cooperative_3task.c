/* Lab-3 Ex13 : Cooperative task scheduling using CONTEXT SWITCHING
   Task1 : running LED pattern on P1.
   Task2 : switch monitoring (P3.2 -> P2.0).
   Task3 : counter increment shown on P0.
   Each task voluntarily yields after one execution cycle.
   Processor context is saved/restored around every switch. */
#include "mcu51.h"

SBIT(SW,   0xB2);          /* P3.2 switch */
SBIT(SWLed, 0xA0);         /* P2.0 LED   */

unsigned char pattern = 0x01;
unsigned char counter = 0;
unsigned char current = 0;

void TaskLedPattern(void)   /* one cycle then yield */
{
    P1 = pattern;
    pattern = pattern << 1;
    if(pattern == 0) pattern = 0x01;
}

void TaskSwitchMonitor(void) /* one cycle then yield */
{
    if(SW == 0)
        SWLed = 0;
    else
        SWLed = 1;
}

void TaskCounter(void)      /* one cycle then yield */
{
    P0 = counter;
    counter++;
}

void Scheduler(void)        /* cooperative : tasks yield themselves */
{
    current = (current + 1) % 3;

    switch(current)
    {
        case 0: TaskLedPattern();   break;
        case 1: TaskSwitchMonitor();break;
        case 2: TaskCounter();      break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
