/* Experiment 27 : Cooperative scheduler (tasks run till they yield)
   Task list + ready queue. Scheduler gives CPU to next ready task. */
#include "mcu51.h"

#define NUM_TASKS 3
#define READY    1
#define RUNNING  0

unsigned char taskState[NUM_TASKS] = {RUNNING, READY, READY};
unsigned char current = 0;

void Task1(void) { P1 ^= 0x01; }   /* LED task   */
void Task2(void) { P1 ^= 0x02; }
void Task3(void) { P1 ^= 0x04; }

void Scheduler(void)
{
    unsigned char i;

    /* current task yields -> it becomes ready again */
    taskState[current] = READY;

    /* pick next ready task (round robin order) */
    for(i = 0; i < NUM_TASKS; i++)
    {
        current = (current + 1) % NUM_TASKS;
        if(taskState[current] == READY)
        {
            taskState[current] = RUNNING;
            return;
        }
    }
}

void ExecuteCurrentTask(void)
{
    switch(current)
    {
        case 0: Task1(); break;
        case 1: Task2(); break;
        case 2: Task3(); break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();           /* context switch: choose next task */
        ExecuteCurrentTask();  /* run it                          */
    }
}
