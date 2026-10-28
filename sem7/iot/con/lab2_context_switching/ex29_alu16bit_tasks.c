/* Lab-2 Activities Ex2 : 16-bit ALU using CONTEXT SWITCHING
   Tasks: 16-bit ADD, SUB, MUL (low/high), DIV.
   Task0 : read the two 16-bit operands (from ports/code).
   Task1 : 16-bit ADD -> store sum + carry.
   Task2 : 16-bit SUB -> store diff + borrow.
   Task3 : 16-bit MUL -> store product low+high.
   Task4 : 16-bit DIV -> store quotient + remainder.
   Results are stored in memory and displayed on P1/P2. */
#include "mcu51.h"

unsigned int x = 0x1234;
unsigned int y = 0x0008;

unsigned int sum, diff, prod, quot, rem;
unsigned char carry, borrow;
unsigned char current = 0;

void TaskAdd16(void)
{
    unsigned long s = (unsigned long)x + y;
    sum = (unsigned int)s;
    carry = (s > 0xFFFF) ? 1 : 0;
}

void TaskSub16(void)
{
    long d = (long)x - y;
    borrow = (d < 0) ? 1 : 0;
    if(d < 0) d = -d;
    diff = (unsigned int)d;
}

void TaskMul16(void)
{
    prod = (unsigned int)((unsigned long)x * y);   /* low word */
}

void TaskDiv16(void)
{
    if(y != 0)
    {
        quot = x / y;
        rem  = x % y;
    }
    else { quot = 0; rem = 0; }
}

void TaskDisplay(void)
{
    unsigned char i;
    for(i = 0; i < 5; i++)
    {
        switch(i)
        {
            case 0: P1 = (unsigned char)sum;   P2 = (unsigned char)(sum>>8);  break;
            case 1: P1 = (unsigned char)diff;  P2 = (unsigned char)(diff>>8); break;
            case 2: P1 = (unsigned char)prod;  P2 = (unsigned char)(prod>>8); break;
            case 3: P1 = (unsigned char)quot;  P2 = 0; break;
            case 4: P1 = (unsigned char)rem;   P2 = 0; break;
        }
        { unsigned int d1, d2; for(d1=0;d1<30;d1++) for(d2=0;d2<1000;d2++); }
    }
}

void Scheduler(void)             /* context switch between ALU tasks */
{
    current = (current + 1) % 5;

    switch(current)
    {
        case 0: TaskAdd16();  break;
        case 1: TaskSub16();  break;
        case 2: TaskMul16();  break;
        case 3: TaskDiv16();  break;
        case 4: TaskDisplay();break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
