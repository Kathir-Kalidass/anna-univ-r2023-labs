/* Lab-3 Ex3 : Complement an 8-bit number using CONTEXT SWITCHING
   Task1 : read an 8-bit number from P0 into a shared variable.
   Task2 : take 1's complement (CPL) and display on P1.
   Scheduler alternates the tasks; variable = saved context. */
#include "mcu51.h"

unsigned char input = 0;
unsigned char result = 0;
unsigned char current = 0;

void TaskReadNumber(void)
{
    input = P0;               /* read 8-bit number from Port 0 */
}

void TaskComplement(void)
{
    result = ~input;          /* 1's complement  */
    P1 = result;              /* display on LEDs */
}

void Scheduler(void)
{
    if(current == 0)
    {
        TaskReadNumber();
        current = 1;          /* context switch */
    }
    else
    {
        TaskComplement();
        current = 0;          /* context switch back */
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
