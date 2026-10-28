/* Save and restore ACC concept with a simulated stack buffer. */
#include "mcu51.h"

unsigned char stk[4];
unsigned char top = 0;
unsigned char accShadow = 0x3C;

void Push(unsigned char v)
{
    if(top < 4)
        stk[top++] = v;
}

unsigned char Pop(void)
{
    if(top > 0)
        return stk[--top];
    return 0;
}

void FunctionA(void)
{
    Push(accShadow);
    accShadow = 0xA5;
    P1 = accShadow;
    accShadow = Pop();
}

void main(void)
{
    while(1)
        FunctionA();
}
