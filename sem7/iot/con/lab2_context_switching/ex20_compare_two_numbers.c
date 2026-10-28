/* Lab-3 Ex8 : Compare two numbers using CONTEXT SWITCHING
   Task1 : read the first number  (from P0).
   Task2 : read the second number (from P2).
   Task3 : compare and display result:
           P1.0 = 1 when equal, P1.1 = 1 when A>B, P1.2 = 1 when A<B.
   Scheduler runs the three tasks in turn (cooperative). */
#include "mcu51.h"

unsigned char numA = 0;
unsigned char numB = 0;
unsigned char current = 0;

void TaskReadA(void)
{
    numA = P0;
    current = 1;
}

void TaskReadB(void)
{
    numB = P2;
    current = 2;
}

void TaskCompare(void)
{
    P1 = 0x00;

    if(numA == numB)      P1 = P1 | 0x01;   /* P1.0 equal */
    else if(numA > numB)  P1 = P1 | 0x02;   /* P1.1 A > B */
    else                  P1 = P1 | 0x04;   /* P1.2 A < B */
    current = 0;
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskReadA();    break;
        case 1: TaskReadB();    break;
        case 2: TaskCompare();  break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
