/* Preemptive priority RTOS simulation using a timer tick. */
#include "mcu51.h"

#define N 3
#define READY   0
#define RUNNING 1
#define WAITING 2

unsigned char state[N] = {RUNNING, READY, READY};
unsigned char prio[N]  = {3, 2, 1};
unsigned int waitN[N]  = {0, 0, 0};
unsigned char current   = 0;
unsigned char schedTick = 0;

void TaskA(void)
{
    P1 ^= 0x01;
    state[0] = WAITING;
    waitN[0] = 2;
}

void TaskB(void)
{
    static unsigned char c = 0;
    P2 = ++c;
    state[1] = WAITING;
    waitN[1] = 4;
}

void TaskC(void)
{
    P1 ^= 0x80;
    state[2] = WAITING;
    waitN[2] = 6;
}

void Scheduler(void)
{
    unsigned char i;
    int best = -1;

    if(state[current] == RUNNING)
        state[current] = READY;

    for(i = 0; i < N; i++)
    {
        if(state[i] == READY)
        {
            if(best < 0 || prio[i] > prio[best])
                best = i;
        }
    }

    if(best >= 0)
    {
        current = (unsigned char)best;
        state[current] = RUNNING;
    }
}

void ExecuteTask(void)
{
    switch(current)
    {
        case 0: TaskA(); break;
        case 1: TaskB(); break;
        case 2: TaskC(); break;
    }
}

ISR(timer0_isr, 1)
{
    unsigned char i;

    TH0 = 0xFC;
    TL0 = 0x66;

    for(i = 0; i < N; i++)
    {
        if(state[i] == WAITING)
        {
            if(waitN[i] > 0)
                waitN[i]--;

            if(waitN[i] == 0)
                state[i] = READY;
        }
    }

    schedTick = 1;
}

void main(void)
{
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while(1)
    {
        if(schedTick)
        {
            schedTick = 0;
            Scheduler();
            ExecuteTask();
        }
    }
}
