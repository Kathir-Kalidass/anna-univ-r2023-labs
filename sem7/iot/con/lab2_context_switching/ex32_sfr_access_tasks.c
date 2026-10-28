/* Lab-2 Activities Ex6 : Accessing SFRs (80H-FFH) using CONTEXT SWITCHING
   Task0 : read a list of SFRs (P0, P1, ACC, B, PSW, SP, DPL, DPH).
   Task1 : store every value read into memory.
   Task2 : display the captured SFR table on P1 (one value at a time).
   Context switching keeps the capture/display loop in step. */
#include "mcu51.h"

unsigned char sfrValues[8];
unsigned char sfrIndex = 0;
unsigned char current  = 0;

void TaskReadSFRs(void)
{
    sfrValues[0] = P0;       /* Port 0  */
    sfrValues[1] = P1;       /* Port 1  */
    sfrValues[2] = ACC;      /* A register   (E0H) */
    sfrValues[3] = B;        /* B register   (F0H) */
    sfrValues[4] = PSW;      /* PSW          (D0H) */
    sfrValues[5] = SP;       /* Stack Ptr    (81H) */
    sfrValues[6] = DPL;      /* DPTR low     (82H) */
    sfrValues[7] = DPH;      /* DPTR high    (83H) */
    current = 1;
}

void TaskStoreSFRs(void)
{
    /* values are already in memory; here we simply show which
       SFR is being stored by lighting the corresponding LED */
    P2 = sfrIndex;
    current = 2;
}

void TaskDisplaySFRs(void)
{
    P1 = sfrValues[sfrIndex];    /* display SFR number sfrIndex */
    sfrIndex = (sfrIndex + 1) & 0x07;
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskReadSFRs();   break;
        case 1: TaskStoreSFRs();  break;
        case 2: TaskDisplaySFRs();break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
