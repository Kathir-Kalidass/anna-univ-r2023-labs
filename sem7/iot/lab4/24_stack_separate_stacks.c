/* Simulated separate stacks for three tasks. */
#include "mcu51.h"

#define NUM_TASKS 3

unsigned char tcbSP[NUM_TASKS];
unsigned char stack1[12];
unsigned char stack2[12];
unsigned char stack3[12];
unsigned char current = 0;

void SetSP(unsigned char *stack, unsigned char size, unsigned char t)
{
    unsigned char newSP;

    newSP = (unsigned char)(((unsigned int)stack + size) & 0xFF);
    if(newSP == 0)
        newSP = 0x80;

    SP = newSP;
    tcbSP[t] = newSP;
}

void Task0(void)
{
    unsigned char local = 0x01;
    P1 = local;
}

void Task1(void)
{
    unsigned char local = 0x02;
    P1 = local;
}

void Task2(void)
{
    unsigned char local = 0x04;
    P1 = local;
}

void Scheduler(void)
{
    tcbSP[current] = SP;
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
        Scheduler();
}
