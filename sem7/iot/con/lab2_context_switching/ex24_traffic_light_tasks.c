/* Lab-3 Ex12 : Traffic light controller using CONTEXT SWITCHING
   Timer0 ISR counts time (one unit = 10 ticks = 50 ms with 5 ms tick).
   Task0 : GREEN phase  (P1.0) for 3 time units.
   Task1 : YELLOW phase (P1.1) for 1 time unit.
   Task2 : RED phase    (P1.2) for 3 time units.
   Task3 : TIMING task  - advances the phase counter.
   Every phase is an independent task that runs when the scheduler
   selects it - classic context-switching traffic controller. */
#include "mcu51.h"

SBIT(GREEN,  0x90);        /* P1.0 */
SBIT(YELLOW, 0x91);        /* P1.1 */
SBIT(RED,    0x92);        /* P1.2 */

unsigned char phase    = 0;      /* 0=GREEN 1=YELLOW 2=RED */
unsigned char phaseCtr = 0;      /* time spent in phase     */
unsigned char current  = 0;

void TaskGreen(void)
{
    GREEN  = 1;
    YELLOW = 0;
    RED    = 0;
}

void TaskYellow(void)
{
    GREEN  = 0;
    YELLOW = 1;
    RED    = 0;
}

void TaskRed(void)
{
    GREEN  = 0;
    YELLOW = 0;
    RED    = 1;
}

void TaskTiming(void)            /* advances the light cycle */
{
    if(phaseCtr == 0)            /* phase finished? */
    {
        phase = (phase + 1) % 3; /* next light      */
        if(phase == 0) phaseCtr = 2;   /* GREEN = 3 units */
        if(phase == 1) phaseCtr = 0;   /* YELLOW = 1 unit */
        if(phase == 2) phaseCtr = 2;   /* RED    = 3 units */
    }
    else
        phaseCtr--;
}

ISR(Timer0ISR, 1)               /* 5 ms tick */
{
    static unsigned char tickCtr = 0;

    TH0 = 0xEC;
    TL0 = 0x78;

    tickCtr++;
    if(tickCtr >= 10)            /* one time unit = 50 ms */
    {
        tickCtr = 0;
        phaseCtr++;
    }

    current = (current + 1) % 4; /* preemptive context switch */
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskGreen();   break;
        case 1: TaskYellow();  break;
        case 2: TaskRed();     break;
        case 3: TaskTiming();  break;
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
