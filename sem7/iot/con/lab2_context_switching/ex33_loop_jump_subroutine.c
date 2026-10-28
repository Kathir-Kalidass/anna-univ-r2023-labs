/* Lab-2 Activities Ex7 : Loops, jumps & subroutine execution
   using CONTEXT SWITCHING
   Task0 : loop task   - count iterations (DJNZ style) with counter.
   Task1 : conditional-jump task - branch on flag (JZ/JNZ/JB style).
   Task2 : subroutine task - call helper functions (LCALL/ACALL style).
   Scheduler switches between the tasks; each task keeps its own
   counters as context. */
#include "mcu51.h"

unsigned char loopCtr  = 0;
unsigned char jumpFlag = 0;
unsigned char sum      = 0;
unsigned char current  = 0;

unsigned char SubAdd(unsigned char x, unsigned char y)  /* subroutine */
{
    return x + y;
}

unsigned char SubMul(unsigned char x, unsigned char y)  /* subroutine */
{
    return x * y;
}

void TaskLoop(void)                     /* looping */
{
    loopCtr++;
    if(loopCtr > 15)
        loopCtr = 0;
    P2 = loopCtr;
}

void TaskConditionalJump(void)          /* jumps */
{
    jumpFlag = (jumpFlag + 1) % 3;      /* 0,1,2 rotating */

    if(jumpFlag == 0)      P1 = 0x00;   /* JZ  : flag zero */
    else if(jumpFlag == 1) P1 = 0xAA;   /* JNZ : flag not zero */
    else                   P1 = 0x55;   /* JB  : bit set */
}

void TaskSubroutine(void)               /* subroutines */
{
    sum = SubAdd(3, 4);                 /* LCALL SubAdd */
    sum = SubMul(sum, 2);               /* LCALL SubMul */
    P0 = sum;
}

void Scheduler(void)                    /* context switch */
{
    current = (current + 1) % 3;

    switch(current)
    {
        case 0: TaskLoop();            break;
        case 1: TaskConditionalJump(); break;
        case 2: TaskSubroutine();      break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
