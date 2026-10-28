/* Lab-3 Ex10 : Bit-status detection using CONTEXT SWITCHING
   Task1 : read an 8-bit number from P0.
   Task2 : check bit 3 of the number and set/clear P1.3.
   Scheduler alternates the two tasks. (Change `BIT_NO` to check
   any other bit of the number.) */
#include "mcu51.h"

#define BIT_NO 3

unsigned char number = 0;
unsigned char current = 0;

void TaskReadNumber(void)
{
    number = P0;
}

void TaskBitCheck(void)
{
    if((number & (1 << BIT_NO)) != 0)
        P1 = (P1 & 0xF7) | 0x08;   /* bit3 of number set -> P1.3 ON */
    else
        P1 = (P1 & 0xF7);          /* clear P1.3                    */
}

void Scheduler(void)
{
    current = (current + 1) % 2;

    if(current == 0)
        TaskReadNumber();
    else
        TaskBitCheck();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
