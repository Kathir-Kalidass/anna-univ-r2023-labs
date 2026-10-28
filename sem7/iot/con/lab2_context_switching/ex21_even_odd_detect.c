/* Lab-3 Ex9 : Even/Odd detection using CONTEXT SWITCHING
   Task1 : read an 8-bit number (P0).
   Task2 : check LSB - if set, number is ODD; else EVEN.
           P1.0 = 1 when EVEN, P1.7 = 1 when ODD.
   Scheduler alternates the two tasks. */
#include "mcu51.h"

unsigned char number = 0;
unsigned char current = 0;

void TaskReadNumber(void)
{
    number = P0;
}

void TaskEvenOdd(void)
{
    P1 = 0x00;

    if((number & 0x01) == 0)
        P1 = P1 | 0x01;          /* EVEN -> P1.0 */
    else
        P1 = P1 | 0x80;          /* ODD  -> P1.7 */
}

void Scheduler(void)
{
    current = (current + 1) % 2;

    if(current == 0)
        TaskReadNumber();
    else
        TaskEvenOdd();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
