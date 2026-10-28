/* Lab-3 Ex2 : Port monitoring using CONTEXT SWITCHING
   Task1 : read the status of switches on P3.
   Task2 : display the switch status on LEDs on P1.
   Periodic context switching between the two tasks. */
#include "mcu51.h"

unsigned char swStatus = 0;
unsigned char current  = 0;

void TaskReadSwitches(void)
{
    swStatus = P3;              /* read switch status (input port) */
}

void TaskDisplayStatus(void)
{
    P1 = swStatus;              /* show status on LEDs (output) */
}

void Scheduler(void)
{
    current = (current + 1) % 2;   /* periodic context switch */

    if(current == 0)
        TaskReadSwitches();
    else
        TaskDisplayStatus();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
