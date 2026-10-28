# Lab Manual — Part 05: Multi-File RTOS Kernel Project

**Aim:** Build the context-switching RTOS demo as a **real multi-file project** — like a
kernel where each task is its own module. This is the "application-oriented" version of
context switching that faculty like to see in later labs.

Project files (all in `src/05_multifile/`):

| File | Role |
|------|------|
| `mcu51.h` | portable header (must sit next to the sources) |
| `tasks.h` | shared declarations (prototypes, NUM_TASKS, ISR prototype) |
| `task1.c` | Task 1 - LED pattern task (P1 ^= 0x55) |
| `task2.c` | Task 2 - switch reading task (P3.2 -> P2.0) |
| `task3.c` | Task 3 - counter task (P0++) |
| `scheduler.c` | scheduler + Timer0 tick ISR |
| `main.c` | kernel entry point (init + main loop) |

## tasks.h
```c
#ifndef TASKS_H
#define TASKS_H

#include "mcu51.h"

#define NUM_TASKS 3

void TaskLED(void);
void TaskSwitch(void);
void TaskCounter(void);

void Scheduler(void);
void ExecuteTask(void);
void TimerInit(void);
unsigned char TimerSchedulerTick(void);

ISR(timer0_isr, 1);

#endif
```

## task1.c / task2.c / task3.c
```c
/* task1.c - Task 1 : LED pattern task */
#include "mcu51.h"
#include "tasks.h"

void TaskLED(void)
{
    P1 ^= 0x55;     /* toggle alternate LED pattern */
}
```
```c
/* task2.c - Task 2 : switch reading task (P3.2 -> P2.0) */
#include "mcu51.h"
#include "tasks.h"

void TaskSwitch(void)
{
    if((P3 & 0x04) == 0)      /* P3.2 pressed? */
        P2 = P2 | 0x01;
    else
        P2 = P2 & 0xFE;
}
```
```c
/* task3.c - Task 3 : counter task (displayed on P0) */
#include "mcu51.h"
#include "tasks.h"

static unsigned char cnt = 0;

void TaskCounter(void)
{
    cnt++;
    P0 = cnt;
}
```

## scheduler.c
```c
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
```

## main.c
```c
#include "mcu51.h"
#include "tasks.h"

void main(void)
{
    TimerInit();             /* start tick timer */

    while(1)
    {
        if(TimerSchedulerTick())   /* a tick occurred ? */
        {
            Scheduler();           /* context switch    */
            ExecuteTask();         /* run next task     */
        }
    }
}
```

## How to run in MCU 8051 IDE
1. Copy the whole `src/05_multifile/` folder to your lab machine.
2. **File → New project**; **Project → Add files to project** and add
   `task1.c`, `task2.c`, `task3.c`, `scheduler.c`, `main.c`
   (`mcu51.h` and `tasks.h` stay in the folder, they are included).
3. **Project → Compile** — MCU 8051 IDE compiles every file and links them.
4. **Simulation → Run** and open:
   - **Ports → Port 1** (TaskLED alternates 0x55/0xAA),
   - **Ports → Port 0** (TaskCounter counts up),
   - **Ports → Port 2** (TaskSwitch mirrors P3.2),
   - **Timers/Counter 0** and **Interrupts** (tick is running).

## Explanation (architecture)
- `main.c` is the kernel loop: wait for a tick → schedule → execute.
- `scheduler.c` owns the scheduler and the tick ISR (the only interrupt in the project).
- Each `taskN.c` is one job; tasks are independent modules — adding a task = new file +
  one case in `ExecuteTask()` + one entry in `tasks.h`.
- The ISR prototype in `tasks.h` is **required by SDCC** for multi-file projects
  (the ISR must be declared in the file containing `main`).

## Result
Multi-file RTOS kernel with Timer0-tick-driven context switching implemented and
simulated successfully.

## Viva
- Why split into files? → modularity; in a real RTOS each driver/task is a module.
- Who owns the interrupt? → the scheduler module (kernel).
- How does the kernel learn that a tick happened? → `tickFlag` set by the ISR, read and
  cleared by `TimerSchedulerTick()` (a tiny event/flag mechanism).
- What happens if two ticks arrive before main reads the flag? → flag is 1 bit; main
  processes one switch per loop; ticks are ~1 ms apart so this is plenty.
