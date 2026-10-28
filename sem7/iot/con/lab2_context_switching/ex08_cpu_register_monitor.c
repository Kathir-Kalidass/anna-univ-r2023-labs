/* Lab-2 Ex8 : Read & display CPU registers using CONTEXT SWITCHING
   Task1 : capture ACC, B, PSW, SP, DPL, DPH, P0, P1 into memory.
   Task2 : display each captured register on P1 (with delay).
   Context switching keeps the captured snapshot valid. */
#include "mcu51.h"

unsigned char regs[8];               /* captured register values   */
unsigned char regIndex = 0;
unsigned char current  = 0;

void Delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 50; i++)
        for(j = 0; j < 1000; j++);
}

void TaskCapture(void)
{
    regs[0] = P0;                    /* read ports */
    regs[1] = P1;
    regs[2] = ACC;                   /* read CPU registers */
    regs[3] = B;
    regs[4] = PSW;
    regs[5] = SP;
    regs[6] = DPL;
    regs[7] = DPH;
    current = 1;
}

void TaskDisplay(void)
{
    P1 = regs[regIndex];             /* show register regIndex */
    regIndex = (regIndex + 1) & 0x07;
    Delay();
}

void Scheduler(void)
{
    if(current == 0)
    {
        TaskCapture();
        current = 1;                 /* context switch */
    }
    else
    {
        TaskDisplay();
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
