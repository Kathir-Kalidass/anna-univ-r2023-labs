/* Lab-3 Ex4 : Left-rotate operation using CONTEXT SWITCHING
   Task1 : rotate the 8-bit value in memory one bit LEFT each run.
   Task2 : display the rotated value on P1.
   Task3 : delay task (gives a visible rotating pattern).
   Scheduler rotates through the three tasks (cooperative). */
#include "mcu51.h"

unsigned char value   = 0x01;   /* initial bit pattern */
unsigned char current = 0;

void TaskRotateLeft(void)
{
    unsigned char carryIn;

    carryIn = (value & 0x80) ? 1 : 0;  /* bit 7 moves to bit 0 */
    value = (value << 1) | carryIn;
}

void TaskDisplay(void)
{
    P1 = value;               /* show rotated pattern on LEDs */
}

void TaskDelay(void)
{
    unsigned int i, j;
    for(i = 0; i < 50; i++)
        for(j = 0; j < 1000; j++);
}

void Scheduler(void)
{
    current = (current + 1) % 3;

    switch(current)
    {
        case 0: TaskRotateLeft(); break;
        case 1: TaskDisplay();    break;
        case 2: TaskDelay();      break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();          /* context switch between the 3 tasks */
    }
}
