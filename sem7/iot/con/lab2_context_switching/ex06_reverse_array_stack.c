/* Lab-2 Ex6 : Reverse an array using STACK (PUSH/POP) + CONTEXT SWITCHING
   Task1 : push array elements [1,2,3,4,5] onto the stack.
   Task2 : pop them back into the array (reversed order).
   Task3 : display the reversed array on P1 one value at a time.
   Simulated stack (array + top pointer) is the shared "task context". */
#include "mcu51.h"

unsigned char arr[5] = {1, 2, 3, 4, 5};
unsigned char stackBuf[8];
unsigned char top = 0;              /* stack pointer  */
unsigned char idx = 0;
unsigned char current = 0;

void Push(unsigned char v)
{
    if(top < 8)
        stackBuf[top++] = v;        /* PUSH */
}

unsigned char Pop(void)
{
    if(top > 0)
        return stackBuf[--top];     /* POP  */
    return 0;
}

void TaskPush(void)
{
    unsigned char i;
    for(i = 0; i < 5; i++)
        Push(arr[i]);
    current = 1;
}

void TaskPopReverse(void)
{
    unsigned char i;
    for(i = 0; i < 5; i++)
        arr[i] = Pop();             /* array now reversed  */
    current = 2;
}

void TaskDisplay(void)
{
    P1 = arr[idx];                  /* show reversed value */
    idx = (idx + 1) % 5;
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskPush();        break;
        case 1: TaskPopReverse();  break;
        case 2: TaskDisplay();     break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();               /* context switch between tasks */
    }
}
