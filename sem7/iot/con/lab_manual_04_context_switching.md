# Lab Manual — Part 04: Context Switching (Exp 24-40)

**Faculty's core question: "Apply context switching in Embedded C using MCU 8051 IDE."**
The 8051 has no RTOS — so we **simulate** context switching in software:

- a **task variable / task table (TCB)** records which task is current,
- the **scheduler** picks the next task,
- the switch point is a **function call, a delay, or the Timer0 tick interrupt**.

Context = PC, SP, A, B, PSW, R0-R7. In these simulations the "state" is the task number
plus the task's own data (counters, patterns).

Watch **Peripherals → Ports → Port 1** in every experiment.

---

## Experiment 24 — Context switching between TWO tasks

**Aim:** Alternate Task1 (0x55) and Task2 (0xAA) using a task variable.
**Algorithm:**
1. If `task==0` run Task1 and set `task=1`.
2. Else run Task2 and set `task=0`.
3. Repeat forever.

**File:** `src/04_context_switching/exp24_two_tasks.c`
```c
#include "mcu51.h"

unsigned char task = 0;      /* current task number */

void Task1(void)
{
    P1 = 0x55;               /* 0101 0101 */
}

void Task2(void)
{
    P1 = 0xAA;               /* 1010 1010 */
}

void main(void)
{
    while(1)
    {
        if(task == 0)        /* Task1 is current */
        {
            Task1();
            task = 1;        /* switch to Task2  */
        }
        else                 /* Task2 is current */
        {
            Task2();
            task = 0;        /* switch to Task1  */
        }
    }
}
```

**Explanation:** `task` is the software "context". Changing it = context switch.
**Output:** 0x55 → 0xAA → 0x55 → 0xAA ...  **Result:** Executed successfully.
**Viva:** Where is the "context" saved here? → In the global variable `task`.
**Modification:** Add `delay()` between switches (Exp 34) or switch on a Timer interrupt
(Exp 29).

---

## Experiment 25 — Context switching among THREE tasks

**File:** `src/04_context_switching/exp25_three_tasks.c`
```c
#include "mcu51.h"

unsigned char task = 0;

void main(void)
{
    while(1)
    {
        switch(task)
        {
            case 0:
                P1 = 0x11;      /* Task 1 */
                task = 1;
                break;

            case 1:
                P1 = 0x22;      /* Task 2 */
                task = 2;
                break;

            case 2:
                P1 = 0x44;      /* Task 3 */
                task = 0;       /* back to Task 1 */
                break;
        }
    }
}
```

**Output:** 0x11 → 0x22 → 0x44 → 0x11 ...  **Result:** Executed successfully.
**Viva:** Why a switch-case? → clean mapping of task number → task code; adding a task is
just another case.

---

## Experiment 26 — Round Robin scheduling (with time quantum)

**Aim:** Three tasks, each gets one "quantum" (the delay) before the scheduler moves on.
**File:** `src/04_context_switching/exp26_round_robin.c`
```c
#include "mcu51.h"

unsigned char current = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)      /* one time quantum */
        for(j = 0; j < 1275; j++);
}

void Task1(void) { P1 ^= 0x01; }   /* toggle bit0 */
void Task2(void) { P1 ^= 0x02; }   /* toggle bit1 */
void Task3(void) { P1 ^= 0x04; }   /* toggle bit2 */

void Scheduler(void)
{
    switch(current)
    {
        case 0: Task1(); current = 1; break;
        case 1: Task2(); current = 2; break;
        case 2: Task3(); current = 0; break;   /* round robin */
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
        delay();        /* time quantum - CPU stays with the task */
    }
}
```

**Explanation:** `Scheduler()` implements the round-robin order 1→2→3→1; the delay is the
**time quantum**. **Output:** P1 bit0, bit1, bit2 toggle in turn.
**Result:** Round robin scheduler executed successfully.
**Viva:** What is a time quantum? → the fixed CPU slice per task. What if a task needs
more time? → it must wait for its next turn.

---

## Experiment 27 — Cooperative scheduler (task list + ready queue)

**Aim:** Tasks run till they finish/yield; the scheduler picks the next ready task.
**File:** `src/04_context_switching/exp27_cooperative_scheduler.c`
```c
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
```

**Explanation:** Each task's `taskState[]` is its TCB state (READY/RUNNING). The scheduler
marks the current task READY (it yielded) and scans for the next READY task. This models a
**cooperative** RTOS: a task must finish/yield for a switch to happen.
**Output:** three LED bits toggle in round-robin order. **Result:** Executed successfully.
**Viva:** Cooperative vs preemptive? → Cooperative switches only when the task yields;
preemptive forces a switch (via timer), see Exp 29/40/44.

---

## Experiment 28 — Priority based scheduling simulation

**Aim:** A high-priority task runs whenever it is requested (switch P3.2 = priority request).
**File:** `src/04_context_switching/exp28_priority_scheduling.c`
```c
#include "mcu51.h"

SBIT(PRIORITY_SW, 0xB2);   /* P3.2 = priority request */

void LowPriorityTask(void)
{
    P1 = 0x0F;               /* 0000 1111 */
}

void HighPriorityTask(void)
{
    P1 = 0xF0;               /* 1111 0000 */
}

void Scheduler(void)
{
    if(PRIORITY_SW == 0)     /* high-priority task requested */
        HighPriorityTask();
    else
        LowPriorityTask();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
```

**In simulator:** press P3.2 (click in Port 3) → P1 shows 0xF0; release → 0x0F.
**Explanation:** This is a static (non-preemptive) priority decision: the ready high
priority task is always chosen first.
**Result:** Priority scheduler executed successfully.
**Viva:** What is priority scheduling? → highest-priority READY task runs first.
**Viva:** What is starvation? → low-priority task never runs because higher tasks are
always ready.
**Modification:** Add a timer to make it preemptive (Exp 44).

---

## Experiment 29 — Context switching using TIMER0 interrupt (FACULTY FAVOURITE)

**Aim:** Timer0 overflow acts as the RTOS tick; the ISR (scheduler) switches tasks.
**Algorithm:**
1. Set Timer0 Mode 1, load TH0/TL0.
2. Enable Timer0 + global interrupts, start timer.
3. On each overflow the ISR switches between Task1 (0x55) and Task2 (0xAA) and reloads.
4. Main loop is empty.

**File:** `src/04_context_switching/exp29_timer_context_switch.c`
```c
#include "mcu51.h"

unsigned char task = 0;

ISR(timer0_isr, 1)
{
    /* --- context switch happens here ---------------------- */
    if(task == 0)
    {
        P1 = 0x55;     /* run Task1  */
        task = 1;      /* next: Task2 */
    }
    else
    {
        P1 = 0xAA;     /* run Task2  */
        task = 0;      /* next: Task1 */
    }

    TH0 = 0xFC;        /* reload timer for next tick */
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;       /* Timer0 Mode 1 (16-bit) */

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;           /* enable Timer0 interrupt */
    EA  = 1;           /* enable global interrupt */

    TR0 = 1;           /* start Timer0 */

    while(1);          /* CPU is free here - scheduler does the job */
}
```

**Explanation:** The timer interrupt **preempts** the CPU every ~1 ms and the ISR acts as
the scheduler → this is how an RTOS switches tasks on a tick. The main loop is free.
**Output:** Port 1 alternates `0101 0101` and `1010 1010` continuously.
**Result:** Timer-based context switching executed successfully.
**Viva:** Why is the timer interrupt used for context switching? → It generates periodic
ticks so the scheduler gets control back regularly (preemptive multitasking).
**Viva:** Why reload TH0/TL0 in the ISR? → to keep the tick period constant.
**Modification:** Add a third task with `task++` and `if(task==3) task=0;`.

---

## Experiment 30 — Context switching using EXTERNAL interrupt INT0

**File:** `src/04_context_switching/exp30_ext_int_context_switch.c`
```c
#include "mcu51.h"

unsigned char task = 0;

ISR(ext0_isr, 0)
{
    if(task == 0)
    {
        P1 = 0x55;      /* Task1 */
        task = 1;
    }
    else
    {
        P1 = 0xAA;      /* Task2 */
        task = 0;
    }
}

void main(void)
{
    EA  = 1;            /* enable global interrupts */
    EX0 = 1;            /* enable INT0             */
    IT0 = 1;            /* falling-edge triggered   */

    while(1);           /* task switch is done in ISR */
}
```

**In simulator:** press P3.2 → P1 switches between 0x55 and 0xAA on every press.
**Result:** External-interrupt context switching executed successfully.
**Viva:** What triggers the switch here? → an **external event** (button), not a timer.

---

## Experiment 31 — Task switching using function calls

**File:** `src/04_context_switching/exp31_function_call_switch.c`
```c
#include "mcu51.h"

void Task1(void)
{
    P1 = 0x0F;      /* 0000 1111 */
}

void Task2(void)
{
    P1 = 0xF0;      /* 1111 0000 */
}

void main(void)
{
    while(1)
    {
        Task1();    /* context switch #1 */
        Task2();    /* context switch #2 */
    }
}
```

**Output:** 0x0F → 0xF0 → 0x0F ... **Result:** Executed successfully.
**Viva:** A C function call *is* a mini context switch — the compiler pushes the return
address (PC) and restores it on return. True RTOS context switching does the same for all
registers.

---

## Experiment 32 — Four-task context switching

**File:** `src/04_context_switching/exp32_four_task_switch.c`
```c
#include "mcu51.h"

unsigned char task = 0;

void main(void)
{
    while(1)
    {
        switch(task)
        {
            case 0:
                P1 = 0x01;
                task++;
                break;

            case 1:
                P1 = 0x02;
                task++;
                break;

            case 2:
                P1 = 0x04;
                task++;
                break;

            case 3:
                P1 = 0x08;
                task = 0;       /* wrap around */
                break;
        }
    }
}
```

**Output:** 0x01 → 0x02 → 0x04 → 0x08 → repeat. **Result:** Executed successfully.
**Viva:** How would you add a 5th task? → add `case 4: ... task=0;` and change `task=0`
to `task=5` in the last case.

---

## Experiment 33 — Software scheduler

**File:** `src/04_context_switching/exp33_software_scheduler.c`
```c
#include "mcu51.h"

unsigned char scheduler = 0;

void main(void)
{
    while(1)
    {
        scheduler++;

        if(scheduler == 1)
            P1 = 0x10;

        else if(scheduler == 2)
            P1 = 0x20;

        else if(scheduler == 3)
        {
            P1 = 0x40;
            scheduler = 0;
        }
    }
}
```

**Output:** 0x10 → 0x20 → 0x40 → repeat. **Result:** Executed successfully.
**Viva:** Here the scheduler is a simple counter; in a real RTOS it is a ready-queue scan.

---

## Experiment 34 — Context switching WITH delay

**File:** `src/04_context_switching/exp34_context_switch_with_delay.c`
```c
#include "mcu51.h"

unsigned char task = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 1275; j++);
}

void Task1(void)
{
    P1 = 0x55;
    delay();         /* hold Task1 output */
}

void Task2(void)
{
    P1 = 0xAA;
    delay();         /* hold Task2 output */
}

void main(void)
{
    while(1)
    {
        if(task == 0)
        {
            Task1();
            task = 1;        /* context switch */
        }
        else
        {
            Task2();
            task = 0;        /* context switch */
        }
    }
}
```

**Output:** 0x55 held ~0.5 s, then 0xAA held ~0.5 s — clearly visible switching.
**Result:** Executed successfully. **Viva:** Delay simulates a task "using the CPU" for
its time slice before yielding (cooperative).

---

## Experiment 35 — Context switching: LED task + Switch task

**File:** `src/04_context_switching/exp35_led_switch_tasks.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */
SBIT(SW,  0xB2);   /* P3.2 */

unsigned char current = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 200; i++)
        for(j = 0; j < 1275; j++);
}

void LEDTask(void)
{
    LED = !LED;          /* blink */
    delay();
}

void SwitchTask(void)
{
    if(SW == 0)
        P1 = P1 | 0x80;  /* set bit7  */
    else
        P1 = P1 & 0x7F;  /* clear bit7 */
}

void Scheduler(void)
{
    current = (current + 1) % 2;   /* alternate 0 <-> 1 */
}

void main(void)
{
    while(1)
    {
        Scheduler();

        switch(current)
        {
            case 0: LEDTask(); break;
            case 1: SwitchTask(); break;
        }
    }
}
```

**Explanation:** Two *different* tasks (LED blink + switch read) share the CPU via the
scheduler — this is the classic "LED and switch task" question.
**Result:** Executed successfully. **Modification:** swap the scheduler order, or add a
third task.

---

## Experiment 36 — Two counter tasks (multitasking demo)

**File:** `src/04_context_switching/exp36_counter_tasks.c`
```c
#include "mcu51.h"

unsigned char current  = 0;
unsigned char evenCnt = 0;
unsigned char oddCnt  = 0;

void Task1(void)
{
    evenCnt += 2;                    /* 0,2,4,6,... */
    P1 = (P1 & 0xF0) | (evenCnt & 0x0F);
}

void Task2(void)
{
    oddCnt += 2;                     /* 1,3,5,7,... */
    P1 = (P1 & 0x0F) | ((oddCnt << 4) & 0xF0);
}

void Scheduler(void)
{
    current = (current + 1) % 2;
}

void main(void)
{
    P1 = 0x00;

    while(1)
    {
        Scheduler();

        if(current == 0)
            Task1();
        else
            Task2();
    }
}
```

**Explanation:** Both counters progress even though the CPU executes one task at a time
— that is the point of multitasking. Lower nibble of P1 = even counter, upper nibble =
odd counter.
**Result:** Executed successfully. **Viva:** Which task holds which data? → `evenCnt`
(Task1) and `oddCnt` (Task2) are the tasks' private "context".

---

## Experiment 37 — RTOS simulation (task states + scheduler)

**Aim:** Model an RTOS kernel: each task has a state (READY/RUNNING); the scheduler scans
the task list and runs the first READY task.
**File:** `src/04_context_switching/exp37_rtos_simulation.c`
```c
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
```

**Explanation:** `taskState[]` = the TCBs. The scheduler marks the finished task READY and
scans for the next READY one — a mini kernel without a timer (cooperative). Watch P0
(counter), P1 (pattern) and P2 (switch) all running "at the same time".
**Result:** RTOS simulation executed successfully.
**Viva:** Where would a real RTOS store the saved registers? → on each task's stack,
referenced by its TCB.

---

## Experiment 38 — Sensor + LED tasks

**File:** `src/04_context_switching/exp38_sensor_led_tasks.c`
```c
#include "mcu51.h"

unsigned char current = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 200; i++)
        for(j = 0; j < 1275; j++);
}

void SensorTask(void)
{
    P0 = P2;         /* copy sensor input to P0 */
}

void LEDTask(void)
{
    P1 = ~P1;        /* toggle all LEDs */
    delay();
}

void Scheduler(void)
{
    current = (current + 1) % 2;
}

void main(void)
{
    while(1)
    {
        Scheduler();

        switch(current)
        {
            case 0: SensorTask(); break;
            case 1: LEDTask();    break;
        }
    }
}
```

**In simulator:** change P2 in the Port 2 window → P0 follows, while P1 blinks
independently. **Result:** Executed successfully.
**Viva:** This shows two independent real-world jobs sharing one CPU.

---

## Experiment 39 — UART + LED tasks

**File:** `src/04_context_switching/exp39_uart_led_tasks.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

unsigned char current = 0;

void UART_Init(void)
{
    TMOD = 0x20;     /* Timer1 Mode 2 (auto reload) */
    TH1  = 0xFD;     /* 9600 baud @ 11.0592 MHz     */
    SCON = 0x50;     /* mode 1, REN enabled         */
    TR1  = 1;
}

void sendChar(unsigned char ch)
{
    SBUF = ch;
    while(TI == 0);
    TI = 0;
}

void sendStr(unsigned char *s)
{
    while(*s)
        sendChar(*s++);
}

void UARTTask(void)
{
    if(current == 0)
        sendStr("T1\n");
    else
        sendStr("T2\n");
}

void LEDTask(void)
{
    LED = !LED;
}

void Scheduler(void)
{
    current = (current + 1) % 2;
}

void main(void)
{
    UART_Init();

    while(1)
    {
        Scheduler();

        switch(current)
        {
            case 0: LEDTask();   break;
            case 1: UARTTask();  break;
        }
    }
}
```

**In simulator:** open **Peripherals → Serial port → terminal**. "T1" and "T2" appear,
while P1.0 blinks — two different jobs (serial + LED) multitasking.
**Result:** Executed successfully. **Viva:** Which registers run the UART? → SBUF, SCON,
and Timer1 (baud). **Viva:** What is a baud rate? → bits per second (here 9600).

---

## Experiment 40 — ENHANCED context switching: mini RTOS with priority + tick

**Aim:** The full RTOS concept on the 8051, single file:
- TCB = three parallel arrays (`taskState`, `taskPrio`, `taskDelay`),
- Timer0 = RTOS tick interrupt (1 ms),
- Scheduler = **priority scheduling** with round-robin tie-break,
- tasks can WAIT (delay) and are woken by the tick — so the high-priority task preempts.

**File:** `src/04_context_switching/exp40_enhanced_context_switch.c`
```c
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
```

**How it works (step by step):**
1. `main` builds the TCB table: prio 3/2/1, all READY except TaskLED (RUNNING).
2. Timer0 ticks every ~1 ms: WAITING tasks count down → become READY; `schedFlag` set.
3. Main loop: `Scheduler()` scans for the READY task with the **highest priority**
   (tie-break = first found), marks it RUNNING, `ExecuteTask()` runs it.
4. TaskLED (prio 3) is ready every 2 ticks → it runs almost always (preemption);
   TaskCounter (prio 2) every 1 tick; TaskBlink (prio 1) every 4 ticks.
5. Watch P1.0/P1.7 and P2 — all three jobs progress, but the high-priority LED runs most
   often. **This is priority scheduling + RTOS tick in Embedded C.**

**Result:** Enhanced context switching / mini-RTOS executed successfully.
**Viva:** Why is this better than Exp 24? → it has a TCB table, priorities, and a tick
that wakes sleeping tasks — much closer to a real RTOS.
**Viva:** What is a TCB? → Task Control Block: per-task info (state, priority, delay,
stack/context pointer). Here it is the parallel arrays.
**Viva:** What is preemption? → the tick can force a switch to a higher priority task even
if the current task is not finished.
**Modification:** Add a 4th task (increase NUM_TASKS to 4, add a case); or change a
priority and watch the scheduling change.

---

*Next: Part 05 (lab_manual_05_multifile.md) — the multi-file RTOS project.*
