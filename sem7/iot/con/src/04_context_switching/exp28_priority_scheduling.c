/* Experiment 28 : Priority based scheduling simulation
   High priority task always runs when it is "ready".
   Change 'highPriorityReady' (or make it depend on a switch P3.2)
   to see the scheduler switch between tasks. */
#include "mcu51.h"

SBIT(PRIORITY_SW, 0xB2);   /* P3.2 = priority request */

void LowPriorityTask(void)
{
    P1 = 0x0F;               /* 0000 1111 */
}

void HighPriorityTask(void)
{
    P1 = 0xF0;               /* 1111 0000 */
}

void Scheduler(void)
{
    if(PRIORITY_SW == 0)     /* high-priority task requested */
        HighPriorityTask();
    else
        LowPriorityTask();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
