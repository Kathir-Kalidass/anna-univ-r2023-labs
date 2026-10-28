/* Lab-2 Ex1 : Arithmetic operations using CONTEXT SWITCHING
   Choice 1..5 (control variable).
   Task1: Addition      Task2: Subtraction
   Task3: Multiplication Task4: Division
   Task5: Exit (halts)
   Scheduler reads `choice` and runs the matching task.
   Context (ACC, B, PSW) is saved/restored around every switch.
   In simulator: change `choice` (or press P3.0-P3.3 to set it).
   Result shown on P1, carry/zero flag on P2.0 */
#include "mcu51.h"

unsigned char choice = 1;
unsigned char x = 25, y = 5;

#define NUM_TASKS 5
unsigned char ctxACC[NUM_TASKS];
unsigned char ctxB[NUM_TASKS];
unsigned char ctxPSW[NUM_TASKS];

void SaveContext(unsigned char t)
{
    ctxACC[t] = ACC;
    ctxB[t]   = B;
    ctxPSW[t] = PSW;
}

void RestoreContext(unsigned char t)
{
    ACC = ctxACC[t];
    B   = ctxB[t];
    PSW = ctxPSW[t];
}

void TaskAdd(void)  { ACC = x + y; B = 0; PSW = (PSW & 0xFE) | (ACC < x); P1 = ACC; }
void TaskSub(void)  { ACC = x - y; B = 0; PSW = (PSW & 0xFE) | (x < y); P1 = ACC; }
void TaskMul(void)  { ACC = x * y; B = 0; PSW = (PSW & 0xFE);           P1 = ACC; }
void TaskDiv(void)  { if(y != 0) { ACC = x / y; B = x % y; } else ACC = 0xFF; P1 = ACC; }
void TaskExit(void) { while(1); }     /* choice=5 : stop multitasking */

void Scheduler(void)
{
    unsigned char prev = choice - 1;

    SaveContext(prev);                 /* save current task context  */

    switch(choice)
    {
        case 1:  TaskAdd();  break;
        case 2:  TaskSub();  break;
        case 3:  TaskMul();  break;
        case 4:  TaskDiv();  break;
        default: TaskExit(); break;
    }

    RestoreContext(prev);              /* restore it after switching */
}

void main(void)
{
    while(1)
    {
        choice = (P3 & 0x07) + 1;      /* switches P3.0-P3.2 set choice 1..8, clamp */
        if(choice > 5) choice = 1;
        Scheduler();                   /* run chosen task with context switch */
    }
}
