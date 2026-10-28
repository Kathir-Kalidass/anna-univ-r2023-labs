/* Lab-2 Activities Ex12 : Full CONTEXT SWITCHING demonstration
   Four concurrent tasks running under a timer-driven (preemptive)
   scheduler with save/restore of the CPU context.
   Task1 : LED blinking on P1.0.
   Task2 : arithmetic operations (result on P2).
   Task3 : port monitoring (P3.2 -> P1.1).
   Task4 : counter increment on P0.
   Every task resumes exactly where it was interrupted. */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 */
SBIT(LED2, 0x91);          /* P1.1 */
SBIT(SW,   0xB2);          /* P3.2 */

#define NUM_TASKS 4

unsigned char current = 0;
unsigned char counter = 0;
unsigned char arithCtr = 0;

unsigned char ctxACC[NUM_TASKS];
unsigned char ctxB[NUM_TASKS];
unsigned char ctxPSW[NUM_TASKS];
unsigned char ctxSP[NUM_TASKS];
unsigned char ctxDPH[NUM_TASKS];
unsigned char ctxDPL[NUM_TASKS];

void SaveContext(unsigned char t)
{
    ctxACC[t] = ACC;
    ctxB[t]   = B;
    ctxPSW[t] = PSW;
    ctxSP[t]  = SP;
    ctxDPH[t] = DPH;
    ctxDPL[t] = DPL;
}

void RestoreContext(unsigned char t)
{
    ACC  = ctxACC[t];
    B    = ctxB[t];
    PSW  = ctxPSW[t];
    SP   = ctxSP[t];
    DPH  = ctxDPH[t];
    DPL  = ctxDPL[t];
}

void TaskLedBlink(void)
{
    static unsigned char ctr = 0;
    ctr++;
    if(ctr >= 100) { ctr = 0; LED1 = (LED1 == 0) ? 1 : 0; }
}

void TaskArithmetic(void)
{
    arithCtr++;
    P2 = (arithCtr * 7) + (arithCtr * 7) / 2;   /* simple calc, no overflow */
    if(arithCtr > 200) arithCtr = 0;
}

void TaskPortMonitor(void)
{
    if(SW == 0)
        LED2 = 0;            /* switch pressed -> LED on */
    else
        LED2 = 1;
}

void TaskCounter(void)
{
    counter++;
    P0 = counter;
}

ISR(Timer0ISR, 1)          /* preemptive tick every 5 ms */
{
    TH0 = 0xEC;
    TL0 = 0x78;

    SaveContext(current);              /* save running task  */
    current = (current + 1) % NUM_TASKS;
    RestoreContext(current);           /* restore next task   */
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskLedBlink();  break;
        case 1: TaskArithmetic();break;
        case 2: TaskPortMonitor();break;
        case 3: TaskCounter();   break;
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
