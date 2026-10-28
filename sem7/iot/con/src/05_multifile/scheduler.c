/* scheduler.c - Scheduler + RTOS tick timer (Timer0 interrupt)
   The tick interrupt is the "scheduler heart beat" - it marks
   that a context switch may happen on the next main-loop pass. */
#include "mcu51.h"
#include "tasks.h"

unsigned char currentTask = 0;
unsigned char tickFlag    = 0;

void Scheduler(void)
{
    currentTask++;
    if(currentTask >= NUM_TASKS)     /* round robin */
        currentTask = 0;
}

void ExecuteTask(void)
{
    switch(currentTask)
    {
        case 0: TaskLED();    break;
        case 1: TaskSwitch(); break;
        case 2: TaskCounter();break;
    }
}

ISR(timer0_isr, 1)
{
    TH0 = 0xFC;              /* reload for ~1 ms tick */
    TL0 = 0x66;
    tickFlag = 1;            /* scheduler wanted!     */
}

void TimerInit(void)
{
    TMOD = 0x01;             /* Timer0 Mode 1 */
    TH0  = 0xFC;
    TL0  = 0x66;
    ET0  = 1;                /* enable Timer0 interrupt */
    EA   = 1;                /* enable global interrupt */
    TR0  = 1;                /* start Timer0 */
}

unsigned char TimerSchedulerTick(void)
{
    unsigned char f = tickFlag;
    tickFlag = 0;
    return f;
}
