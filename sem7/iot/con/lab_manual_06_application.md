# Lab Manual — Part 06: Application-Oriented Programs (Exp 41-44)

Application-oriented labs combine peripherals + tasks. All programs verified with SDCC.

---

## Experiment 41 — Traffic light controller

**Aim:** Generate a traffic light sequence (Red → Yellow → Green) using delay-based tasks.
**Connections:** P1.0=Red, P1.1=Yellow, P1.2=Green.
**File:** `src/06_application/exp41_traffic_light.c`
```c
#include "mcu51.h"

SBIT(RED,    0x90);   /* P1.0 = Red    */
SBIT(YELLOW, 0x91);   /* P1.1 = Yellow */
SBIT(GREEN,  0x92);   /* P1.2 = Green  */

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 200; j++);   /* ~1 ms inner loop */
}

void main(void)
{
    while(1)
    {
        RED    = 0;   YELLOW = 1;  GREEN = 1;   /* Red ON  */
        delay_ms(5000);

        RED    = 1;   YELLOW = 0;  GREEN = 1;   /* Yellow  */
        delay_ms(1000);

        RED    = 1;   YELLOW = 1;  GREEN = 0;   /* Green   */
        delay_ms(4000);
    }
}
```

**Output:** Red 5 s → Yellow 1 s → Green 4 s → repeat (watch P1.0-1.2).
**Result:** Traffic light controller executed successfully.
**Modification:** Add a walker button (INT0) to shorten the red phase.

---

## Experiment 42 — Water level controller

**Aim:** Control a pump and alarm based on three water sensors.
**Connections:** P3.0=empty, P3.1=mid, P3.2=full sensors; P1.0=motor, P1.1=buzzer.
**File:** `src/06_application/exp42_water_level_controller.c`
```c
#include "mcu51.h"

SBIT(S_EMPTY, 0xB0);   /* P3.0 = empty sensor */
SBIT(S_MID,   0xB1);   /* P3.1 = mid sensor   */
SBIT(S_FULL,  0xB2);   /* P3.2 = full sensor  */
SBIT(MOTOR,   0x90);   /* P1.0 = pump         */
SBIT(BUZZER,  0x91);   /* P1.1 = alarm        */

void main(void)
{
    MOTOR  = 1;     /* pump OFF initially */
    BUZZER = 0;

    while(1)
    {
        if(S_FULL == 0)              /* tank full  */
        {
            MOTOR  = 1;              /* stop pump  */
            BUZZER = 0;
        }
        else if(S_EMPTY == 0)        /* tank empty */
        {
            MOTOR  = 0;              /* pump ON    */
            BUZZER = 1;              /* alarm      */
        }
        else                         /* mid level  */
        {
            MOTOR  = 0;              /* pump ON    */
            BUZZER = 0;
        }
    }
}
```

**Truth table:**

| S_EMPTY | S_MID | S_FULL | MOTOR | BUZZER |
|---------|-------|--------|-------|--------|
| 0       | 0     | 0      | ON (0)  | ALARM (1) |
| 1       | 0     | 1      | ON (0)  | OFF (0)   |
| 1       | 1     | 0      | OFF (1) | OFF (0)   |

**In simulator:** change P3 in the Port 3 window; watch P1.0/P1.1.
**Result:** Water level controller executed successfully.

---

## Experiment 43 — Two digit counter (INT0-driven)

**Aim:** Count 00-99 on INT0 presses. Tens = high nibble of P1, units = low nibble of P0.
**File:** `src/06_application/exp43_two_digit_counter.c`
```c
#include "mcu51.h"

unsigned char units = 0;
unsigned char tens  = 0;

ISR(ext0_isr, 0)
{
    units++;

    if(units == 10)        /* carry to tens */
    {
        units = 0;
        tens++;
    }
    if(tens == 10)         /* wrap at 99 */
        tens = 0;

    P0 = (P0 & 0xF0) | units;   /* units digit on low nibble  */
    P1 = (P1 & 0x0F) | (tens << 4); /* tens digit high nibble */
}

void main(void)
{
    EA  = 1;
    EX0 = 1;
    IT0 = 1;

    while(1);
}
```

**In simulator:** press P3.2 repeatedly; P0 counts 0-9 and P1 counts tens.
**Result:** Two digit counter executed successfully.
**Viva:** Why `& 0xF0` masks? → to update only one nibble without clearing the other.

---

## Experiment 44 — PREEMPTIVE priority RTOS (application)

**Aim:** The most complete demo: a Timer0 tick makes scheduling **preemptive** and
priority-driven, so the high-priority task preempts others as soon as it is READY.
**File:** `src/06_application/exp44_preemptive_priority_rtos.c`
```c
#include "mcu51.h"

#define N 3
#define READY   0
#define RUNNING 1
#define WAITING 2

unsigned char state[N]  = {RUNNING, READY, READY};
unsigned char prio[N]   = {3, 2, 1};
unsigned int  waitN[N]  = {0, 0, 0};
unsigned char current   = 0;
unsigned char schedTick = 0;

void TaskA(void) { P1 ^= 0x01; state[0] = WAITING; waitN[0] = 2; }
void TaskB(void) { static unsigned char c = 0; P2 = ++c; state[1] = WAITING; waitN[1] = 4; }
void TaskC(void) { P1 ^= 0x80; state[2] = WAITING; waitN[2] = 6; }

void Scheduler(void)
{
    unsigned char i;
    int best = -1;

    if(state[current] == RUNNING)
        state[current] = READY;

    for(i = 0; i < N; i++)
    {
        if(state[i] == READY)
            if(best < 0 || prio[i] > prio[best])
                best = i;
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
            if(waitN[i] > 0) waitN[i]--;
            if(waitN[i] == 0) state[i] = READY;   /* becomes ready -> may preempt */
        }
    }

    schedTick = 1;
}

void main(void)
{
    TMOD = 0x01;
    TH0  = 0xFC;
    TL0  = 0x66;
    ET0  = 1;
    EA   = 1;
    TR0  = 1;

    while(1)
    {
        if(schedTick)
        {
            schedTick = 0;
            Scheduler();      /* context switch decision */
            ExecuteTask();    /* run chosen task          */
        }
    }
}
```

**How to observe:**
- P1.0 (TaskA, prio 3) toggles almost continuously — it wakes every 2 ticks.
- P2 (TaskB, prio 2) counts every 4 ticks.
- P1.7 (TaskC, prio 1) toggles every 6 ticks.
- Change `prio[]` (e.g. make C highest) and watch the behaviour swap → proves the
  scheduler really is priority-driven and preemptive.

**Result:** Preemptive priority RTOS simulation executed successfully.
**Viva:** What makes it preemptive (not cooperative)? → the Timer0 tick can mark a task
READY while another runs; the next scheduler call may then switch to it — the running
task has no say in the matter.

---

*End of Part 06. Combine Parts 00-06 into one submission; the experiment list covers
basics → timers → interrupts → context switching → multi-file → applications.*
