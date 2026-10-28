/* tasks.h - shared declarations for the multi-file RTOS demo
   Add ALL files to one project:
     mcu51.h, tasks.h, task1.c, task2.c, task3.c, scheduler.c, main.c  */
#ifndef TASKS_H
#define TASKS_H

#include "mcu51.h"

#define NUM_TASKS 3

/* task functions */
void TaskLED(void);
void TaskSwitch(void);
void TaskCounter(void);

/* scheduler / kernel */
void Scheduler(void);
void ExecuteTask(void);
void TimerInit(void);
unsigned char TimerSchedulerTick(void);

/* ISR prototype - MUST match the definition (interrupt attribute)
   and be visible in the file containing main (SDCC requirement) */
ISR(timer0_isr, 1);

#endif
