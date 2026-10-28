/* Lab-2 Ex2 : Count number of 1's using CONTEXT SWITCHING
   Task1 : read an 8-bit number (from P0, or internal).
   Task2 : count the bits that are set -> store count in memory,
           show it on P1.
   Scheduler alternates the two tasks (cooperative). */
#include "mcu51.h"

unsigned char inputNumber = 0;
unsigned char onesCount   = 0;
unsigned char current      = 0;

void TaskRead(void)
{
    inputNumber = P0;       /* take number from Port 0 in the simulator */
    current = 1;            /* context switch -> next task */
}

void TaskCountOnes(void)
{
    unsigned char temp = inputNumber;
    unsigned char cnt  = 0;

    while(temp)
    {
        if(temp & 0x01)     /* bit set ? */
            cnt++;
        temp >>= 1;
    }

    onesCount = cnt;        /* store result in memory */
    P1 = cnt;               /* display count on LEDs */
    current = 0;            /* context switch -> back to TaskRead */
}

void Scheduler(void)
{
    if(current == 0)
        TaskRead();
    else
        TaskCountOnes();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
