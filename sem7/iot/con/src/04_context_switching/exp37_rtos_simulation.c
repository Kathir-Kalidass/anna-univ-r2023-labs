/* Experiment 37 : RTOS simulation - task states + scheduler
   Each task has a state (READY/RUNNING). The scheduler scans the
   ready list and gives the CPU to the first ready task (round robin).
   This models how an RTOS keeps a task list and switches contexts. */
#include "mcu51.h"

#define NUM_TASKS 3
#define READY    1
#define RUNNING  0

unsigned char taskState[NUM_TASKS] = {RUNNING, READY, READY};
unsigned char currentTask = 0;

void TaskLED(void)      /* Task 1 : LED pattern   */
{
    P1 ^= 0x55;
}

void TaskSwitch(void)   /* Task 2 : read switch P3.2 -> P2.0 */
{
    if((P3 & 0x04) == 0)
        P2 = P2 | 0x01;
    else
        P2 = P2 & 0xFE;
}

void TaskCounter(void)  /* Task 3 : running counter on P0 */
{
    static unsigned char cnt = 0;
    cnt++;
    P0 = cnt;
}

void Scheduler(void)
{
    unsigned char i;

    /* current task finishes -> becomes ready */
    taskState[currentTask] = READY;

    /* round robin : find next ready task */
    for(i = 0; i < NUM_TASKS; i++)
    {
        currentTask = (currentTask + 1) % NUM_TASKS;
        if(taskState[currentTask] == READY)
        {
            taskState[currentTask] = RUNNING;
            return;
        }
    }
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

void main(void)
{
    while(1)
    {
        Scheduler();       /* pick next task  */
        ExecuteTask();     /* run that task   */
    }
}
