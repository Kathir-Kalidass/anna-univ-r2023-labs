/* Simulated stack PUSH/POP demo using a small RAM buffer. */
#include "mcu51.h"

unsigned char stk[8];
unsigned char top = 0;
unsigned char val = 0x10;
unsigned char res[4];
unsigned char rIdx = 0;
unsigned char ok = 1;
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
    val = val + 0x01;
    Push(val);
    current = 1;
}

void TaskPop(void)
{
    res[rIdx] = Pop();
    rIdx++;

    if(rIdx == 4)
        current = 2;
    else
        current = 0;
}

void TaskVerify(void)
{
    if(res[0] == 0x14 && res[1] == 0x13 && res[2] == 0x12 && res[3] == 0x11)
        ok = 1;
    else
        ok = 0;

    P1 = ok ? 0xAA : 0x00;
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskPush();  break;
        case 1: TaskPop();   break;
        case 2: TaskVerify(); break;
    }
}

void main(void)
{
    while(1)
        Scheduler();
}
