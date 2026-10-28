/* Lab-2 Activities Ex11 : Preemptive CONTEXT SWITCHING
   Timer0 interrupt interrupts the currently running task and
   switches to the next one. The ISR saves ACC, B, PSW, SP,
   DPH, DPL into the task control block and restores the next
   task's context. (The PC is saved automatically by the CPU
   onto the stack and restored by RETI.)
   Task0 : blink LED on P1.0     Task1 : counter on P0
   Task2 : rotate pattern on P1 */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 */

#define NUM_TASKS 3

unsigned char current = 0;
unsigned char counter = 0;
unsigned char pattern = 0x01;

/* task control blocks : saved CPU context per task */
unsigned char ctxACC[NUM_TASKS];
unsigned char ctxB[NUM_TASKS];
unsigned char ctxPSW[NUM_TASKS];
unsigned char ctxSP[NUM_TASKS];
unsigned char ctxDPH[NUM_TASKS];
unsigned char ctxDPL[NUM_TASKS];

void SaveContext(unsigned char t)    /* save CPU context */
{
    ctxACC[t] = ACC;
    ctxB[t]   = B;
    ctxPSW[t] = PSW;
    ctxSP[t]  = SP;
    ctxDPH[t] = DPH;
    ctxDPL[t] = DPL;
}

void RestoreContext(unsigned char t) /* restore CPU context */
{
    ACC  = ctxACC[t];
    B    = ctxB[t];
    PSW  = ctxPSW[t];
    SP   = ctxSP[t];
    DPH  = ctxDPH[t];
    DPL  = ctxDPL[t];
}

void TaskBlink(void)
{
    static unsigned char ctr = 0;
    ctr++;
    if(ctr >= 100) { ctr = 0; LED1 = (LED1 == 0) ? 1 : 0; }
}

void TaskCounter(void)
{
    counter++;
    P0 = counter;
}

void TaskRotate(void)
{
    P1 = pattern;
    pattern = pattern << 1;
    if(pattern == 0) pattern = 0x01;
}

ISR(Timer0ISR, 1)          /* preemptive tick every 5 ms */
{
    TH0 = 0xEC;
    TL0 = 0x78;

    SaveContext(current);              /* 1. save running task  */
    current = (current + 1) % NUM_TASKS;
    RestoreContext(current);           /* 2. restore next task  */
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskBlink();   break;
        case 1: TaskCounter(); break;
        case 2: TaskRotate();  break;
    }
}

void main(void)
{
    TMOD = 0x01;
    TH0 = 0xEC; TL0 = 0x78;
    ET0 = 1;
    EA  = 1;
    TR0 = 1;

    while(1)
    {
        Scheduler();
    }
}
