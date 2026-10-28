/* Lab-2 Activities Ex1 : 8-bit ALU using CONTEXT SWITCHING
   One task per ALU operation - 12 tasks in total:
   ADD, SUB, MUL, DIV, AND, OR, XOR, RL, RR, CPL, CLR, SETB.
   Every task performs its operation on `a` (and `b`) and stores
   the result in `res`. A round-robin scheduler with a delay
   between switches shows each result on P1. */
#include "mcu51.h"

unsigned char a   = 0x6A;
unsigned char b   = 0x05;
unsigned char res = 0;
unsigned char current = 0;

void TaskADD(void) { res = a + b; }
void TaskSUB(void) { res = a - b; }
void TaskMUL(void) { res = a * b; }
void TaskDIV(void) { res = (b != 0) ? (a / b) : 0xFF; }
void TaskANL(void) { res = a & b; }
void TaskORL(void) { res = a | b; }
void TaskXRL(void) { res = a ^ b; }
void TaskRL (void) { res = (unsigned char)(res << 1); }
void TaskRR (void) { res = (unsigned char)(res >> 1); }
void TaskCPL(void) { res = (unsigned char)(~res); }
void TaskCLR(void) { res = 0; }
void TaskSETB(void){ res = res | 0x80; }

void TaskDisplay(void)
{
    P1 = res;                       /* show current task result */
    unsigned int i, j;
    for(i = 0; i < 40; i++)
        for(j = 0; j < 1000; j++);
}

void Scheduler(void)                /* round-robin context switch */
{
    current = (current + 1) % 12;

    switch(current)
    {
        case 0:  TaskADD();  break;
        case 1:  TaskSUB();  break;
        case 2:  TaskMUL();  break;
        case 3:  TaskDIV();  break;
        case 4:  TaskANL();  break;
        case 5:  TaskORL();  break;
        case 6:  TaskXRL();  break;
        case 7:  TaskRL();   break;
        case 8:  TaskRR();   break;
        case 9:  TaskCPL();  break;
        case 10: TaskCLR();  break;
        case 11: TaskSETB(); break;
    }

    TaskDisplay();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
