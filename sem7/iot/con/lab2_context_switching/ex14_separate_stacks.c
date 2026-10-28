/* Lab-2 Ex14 : Context switching using SEPARATE STACKS
   Each of the 3 tasks has its own private stack area.
   On a switch the task's SP (0x81) is saved into its control
   block and the next task's SP is restored - each task keeps
   its own local data. */
#include "mcu51.h"

#define NUM_TASKS 3

unsigned char tcbSP[NUM_TASKS];        /* saved SP per task        */
unsigned char stack1[12];
unsigned char stack2[12];
unsigned char stack3[12];
unsigned char current = 0;

void SetSP(unsigned char *stack, unsigned char size, unsigned char t)
{
    unsigned char newSP = (unsigned char)(((unsigned int)stack + size) & 0xFF);
    if(newSP == 0) newSP = 0x80;       /* avoid bank/bit area */
    SP = newSP;                        /* switch to this task's stack */
    tcbSP[t] = newSP;
}

void Task0(void)
{
    unsigned char local = 0x01;
    P1 = local;                        /* task0 LED */
}

void Task1(void)
{
    unsigned char local = 0x02;
    P1 = local;                        /* task1 LED */
}

void Task2(void)
{
    unsigned char local = 0x04;
    P1 = local;                        /* task2 LED */
}

void Scheduler(void)                   /* context switch with SP swap */
{
    tcbSP[current] = SP;               /* save current stack pointer */

    current = (current + 1) % NUM_TASKS;

    switch(current)
    {
        case 0: SetSP(stack1, sizeof(stack1), 0); Task0(); break;
        case 1: SetSP(stack2, sizeof(stack2), 1); Task1(); break;
        case 2: SetSP(stack3, sizeof(stack3), 2); Task2(); break;
    }
}

void main(void)
{
    SetSP(stack1, sizeof(stack1), 0);

    while(1)
    {
        Scheduler();                   /* run tasks on separate stacks */
    }
}
