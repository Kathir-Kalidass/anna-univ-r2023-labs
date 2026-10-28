/* Lab-2 Activities Ex10 : Cooperative CONTEXT SWITCHING
   Task1 : running LED pattern on P1.
   Task2 : switch monitoring (P3.2 -> P2.0).
   Task3 : arithmetic calculation (sum 1..10) shown on P0.
   Each task voluntarily yields after one execution cycle. */
#include "mcu51.h"

SBIT(SW,   0xB2);          /* P3.2 */
SBIT(SWLed, 0xA0);         /* P2.0 */

unsigned char pattern = 0x01;
unsigned char sum     = 0;
unsigned char step    = 0;
unsigned char current = 0;

void TaskLedPattern(void)    /* one step then yield */
{
    P1 = pattern;
    pattern = pattern << 1;
    if(pattern == 0) pattern = 0x01;
}

void TaskSwitchMonitor(void) /* one step then yield */
{
    if(SW == 0)
        SWLed = 0;
    else
        SWLed = 1;
}

void TaskArithmetic(void)    /* one step then yield */
{
    step++;
    sum += step;
    if(step == 10)
    {
        P0 = sum;            /* final result on P0 */
        step = 0;
        sum = 0;
    }
}

void Scheduler(void)
{
    current = (current + 1) % 3;   /* yield -> next task */

    switch(current)
    {
        case 0: TaskLedPattern();   break;
        case 1: TaskSwitchMonitor();break;
        case 2: TaskArithmetic();   break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
