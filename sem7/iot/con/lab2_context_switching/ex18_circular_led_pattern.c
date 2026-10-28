/* Lab-3 Ex5 : Circular LED pattern using CONTEXT SWITCHING
   Task1 : rotate a lit-LED pattern on P1 (circular running light).
   Task2 : timing delay task that paces the rotation.
   Two tasks run alternately - the rotation state (pattern) is the
   shared "task context". */
#include "mcu51.h"

unsigned char pattern = 0x01;
unsigned char current = 0;

void TaskRotateLED(void)
{
    P1 = pattern;                  /* light one LED */
    pattern = pattern << 1;
    if(pattern == 0)               /* bit7 -> bit0 (circular) */
        pattern = 0x01;
}

void TaskDelay(void)
{
    unsigned int i, j;
    for(i = 0; i < 60; i++)
        for(j = 0; j < 1000; j++);
}

void Scheduler(void)
{
    current = (current + 1) % 2;

    if(current == 0)
        TaskRotateLED();
    else
        TaskDelay();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
