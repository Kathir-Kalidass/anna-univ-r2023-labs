/* Lab-3 Ex7 : Complement an 8-bit number using CONTEXT SWITCHING
   Task1 : read an 8-bit number (P0).
   Task2 : complement it, store + display the result (P1).
   The processor context (ACC, B, PSW) is explicitly saved before
   every switch and restored before resuming the saved task. */
#include "mcu51.h"

unsigned char input  = 0;
unsigned char result = 0;
unsigned char current = 0;

#define NUM_SAVED 2

unsigned char ctxACC[NUM_SAVED];
unsigned char ctxB[NUM_SAVED];
unsigned char ctxPSW[NUM_SAVED];

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

void TaskReadNumber(void)
{
    input = P0;
}

void TaskComplement(void)
{
    result = ~input;            /* 1's complement */
    P1 = result;                /* store/display  */
}

void Scheduler(void)
{
    unsigned char prev = current;

    SaveContext(prev);          /* save processor context */

    current = (current + 1) % 2;
    if(current == 0)
        TaskReadNumber();
    else
        TaskComplement();

    RestoreContext(prev);       /* restore before resuming */
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
