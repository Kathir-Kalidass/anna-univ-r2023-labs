/* Experiment 40 : ENHANCED context switching - mini RTOS simulation
   ---------------------------------------------------------------
   A small RTOS-like scheduler on the 8051 (pure software):

   * TCB (Task Control Block) built from parallel arrays
       taskState : 0 = READY, 1 = RUNNING, 2 = WAITING (delayed)
       taskPrio  : higher number = higher priority
       taskDelay : ticks a task must wait before becoming READY

   * Timer0 generates the system tick (like RTOS Tick Interrupt)
     Every tick:  count down WAITING tasks -> they become READY
                  set schedFlag so the main loop schedules again

   * Scheduler = Priority scheduling with round-robin tie-break
     The READY task with the HIGHEST priority is given the CPU.

   * 3 tasks:
       TaskLED    priority 3  toggles P1.0, waits 2 ticks
       TaskCounter priority 2  increments P2,    waits 1 tick
       TaskBlink  priority 1  toggles P1.7, waits 4 ticks
   --------------------------------------------------------------- */
#include "mcu51.h"

#define NUM_TASKS 3

#define READY    0
#define RUNNING  1
#define WAITING  2

/* ---------------- TCB tables ---------------- */
unsigned char taskState[NUM_TASKS];   /* READY / RUNNING / WAITING */
unsigned char taskPrio[NUM_TASKS];    /* priority of each task     */
unsigned int  taskDelay[NUM_TASKS];   /* ticks left to wait        */

unsigned char currentTask = 0;
unsigned int  tickCount   = 0;
unsigned char schedFlag   = 0;

/* ---------------- Task functions ---------------- */
void TaskLED(void)              /* highest priority */
{
    P1 ^= 0x01;                 /* toggle P1.0      */

    taskState[0] = WAITING;     /* yield CPU        */
    taskDelay[0] = 2;           /* wait 2 ticks     */
}

void TaskCounter(void)
{
    static unsigned char cnt = 0;
    cnt++;
    P2 = cnt;                   /* show counter     */

    taskState[1] = WAITING;
    taskDelay[1] = 1;
}

void TaskBlink(void)            /* lowest priority  */
{
    P1 ^= 0x80;                 /* toggle P1.7      */

    taskState[2] = WAITING;
    taskDelay[2] = 4;
}

/* ---------------- Scheduler ---------------- */
void Scheduler(void)
{
    unsigned char i;
    int best = -1;

    /* a finished RUNNING task goes back to READY */
    if(taskState[currentTask] == RUNNING)
        taskState[currentTask] = READY;

    /* pick READY task with highest priority */
    for(i = 0; i < NUM_TASKS; i++)
    {
        if(taskState[i] == READY)
        {
            if(best < 0 || taskPrio[i] > taskPrio[best])
                best = i;
        }
    }

    /* give CPU to chosen task */
    if(best >= 0)
    {
        currentTask = (unsigned char)best;
        taskState[currentTask] = RUNNING;
    }
}

/* ---------------- Execute selected task ---------------- */
void ExecuteTask(void)
{
    switch(currentTask)
    {
        case 0: TaskLED();     break;
        case 1: TaskCounter(); break;
        case 2: TaskBlink();   break;
    }
}

/* ---------------- Timer0 tick (RTOS tick) ---------------- */
ISR(timer0_isr, 1)
{
    unsigned char i;

    TH0 = 0xFC;                /* reload for ~1 ms tick */
    TL0 = 0x66;

    tickCount++;

    /* count down WAITING tasks; they become READY */
    for(i = 0; i < NUM_TASKS; i++)
    {
        if(taskState[i] == WAITING)
        {
            if(taskDelay[i] > 0)
                taskDelay[i]--;

            if(taskDelay[i] == 0)
                taskState[i] = READY;
        }
    }

    schedFlag = 1;             /* ask main loop to schedule */
}

/* ---------------- main ---------------- */
void main(void)
{
    unsigned char i;

    /* initialize TCB table */
    for(i = 0; i < NUM_TASKS; i++)
    {
        taskState[i] = READY;
        taskPrio[i]  = (unsigned char)(NUM_TASKS - i); /* 3,2,1 */
        taskDelay[i] = 0;
    }
    taskState[0] = RUNNING;    /* TaskLED starts first */

    /* start the RTOS tick timer */
    TMOD = 0x01;               /* Timer0 Mode 1       */
    TH0  = 0xFC;
    TL0  = 0x66;

    ET0 = 1;                   /* enable Timer0 int   */
    EA  = 1;                   /* enable global int   */
    TR0 = 1;                   /* start Timer0        */

    /* RTOS main loop: schedule -> execute -> repeat */
    while(1)
    {
        if(schedFlag)
        {
            schedFlag = 0;
            Scheduler();       /* context switch decision */
            ExecuteTask();     /* run the selected task   */
        }
    }
}
