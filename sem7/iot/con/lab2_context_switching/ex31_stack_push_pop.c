/* Lab-2 Activities Ex4 : Stack operations PUSH/POP
   using CONTEXT SWITCHING
   Task0 : PUSH values 0x11..0x14 onto the stack.
   Task1 : POP the values back into a results array.
   Task2 : verify the order (LIFO) and display on P1.
   A simulated stack + top pointer is the shared context. */
#include "mcu51.h"

unsigned char stk[8];
unsigned char top   = 0;
unsigned char val   = 0x10;
unsigned char res[4];
unsigned char rIdx  = 0;
unsigned char ok    = 1;
unsigned char current = 0;

void Push(unsigned char v)
{
    if(top < 8)
        stk[top++] = v;
}

unsigned char Pop(void)
{
    if(top > 0)
        return stk[--top];
    return 0;
}

void TaskPush(void)
{
    val = val + 0x01;           /* 0x11, 0x12, 0x13, 0x14 */
    Push(val);
    current = 1;
}

void TaskPop(void)
{
    res[rIdx] = Pop();
    rIdx++;
    if(rIdx == 4)
        current = 2;            /* all popped -> verify */
    else
        current = 0;
}

void TaskVerify(void)
{
    /* LIFO: res should be 0x14,0x13,0x12,0x11 */
    if(res[0]==0x14 && res[1]==0x13 && res[2]==0x12 && res[3]==0x11)
        ok = 1;
    else
        ok = 0;

    P1 = ok ? 0xAA : 0x00;      /* 0xAA = correct order */
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskPush(); break;
        case 1: TaskPop();  break;
        case 2: TaskVerify();break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
