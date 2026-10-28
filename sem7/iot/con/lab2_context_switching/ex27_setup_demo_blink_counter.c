/* Lab-3 Ex16 : Setup demo - simple 2-task CONTEXT SWITCHING
   Task0 : blink LED on P1.0.
   Task1 : count on P0.
   This is the smallest "getting started" context-switching
   program: two tasks alternated by the scheduler. */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 */

unsigned char current = 0;
unsigned char count   = 0;

void TaskBlink(void)
{
    LED1 = (LED1 == 0) ? 1 : 0;      /* toggle LED */
}

void TaskCount(void)
{
    P0 = count;
    count++;
}

void Scheduler(void)
{
    current = (current + 1) % 2;

    if(current == 0)
        TaskBlink();
    else
        TaskCount();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
