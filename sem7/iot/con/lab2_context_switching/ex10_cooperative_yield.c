/* Lab-2 Ex10 : Cooperative context switching (tasks yield control)
   Task0 : running LED pattern on P1 (yields after each bit).
   Task1 : switch monitor P3.2 -> P2.0 (yields after each read).
   Task2 : arithmetic task: sum 1..10 shown on P0 (yields per add).
   Every task returns (=yields) after one small step so the others
   get CPU time - cooperative scheduling. */
#include "mcu51.h"

SBIT(SW,   0xB2);
SBIT(SWLed, 0xA0);

unsigned char pattern = 0x01;
unsigned char sum     = 0;
unsigned char step    = 0;
unsigned char current = 0;

void TaskLedPattern(void)   /* one step then yield */
{
    P1 = pattern;
    pattern = (pattern << 1);
    if(pattern == 0)
        pattern = 0x01;
}

void TaskSwitch(void)       /* one step then yield */
{
    if(SW == 0)
        SWLed = 0;
    else
        SWLed = 1;
}

void TaskArithmetic(void)   /* one step then yield */
{
    step++;
    sum += step;
    if(step == 10)          /* finished : show total and stop adding */
    {
        P0 = sum;
        step = 0;
    }
}

void Scheduler(void)        /* cooperative : each task yields itself */
{
    current = (current + 1) % 3;

    switch(current)
    {
        case 0: TaskLedPattern(); break;
        case 1: TaskSwitch();     break;
        case 2: TaskArithmetic(); break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
