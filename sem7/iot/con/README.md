# 8051 Embedded C Lab Manual — MCU 8051 IDE (Exam-Ready)

Complete practical record for **MCU 8051 IDE** lab sessions: Embedded C basics, Timers,
Interrupts, **Context Switching / RTOS simulation**, multi-file projects and
application-oriented programs.

All programs are verified to **compile and link with SDCC** (the compiler used by
MCU 8051 IDE) and are also **Keil C51 compatible** through the portable header
`mcu51.h`. Total: **44 single-file programs + 1 multi-file RTOS project**.

---

## Folder layout

```
iot/con/
├── README.md                     <- this file (index + quick start)
├── lab_manual_00_overview.md     <- theory, MCU 8051 IDE setup, how to run,
│                                    syntax table, timer values, viva bank
├── lab_manual_01_basics.md       <- Exp 1-13  (LED, switch, port, operators)
├── lab_manual_02_timers.md       <- Exp 14-18 (Timer0/1 delay, ISR blink,
│                                    square wave, multiple delays)
├── lab_manual_03_interrupts.md   <- Exp 19-23 (INT0, INT1, Timer0 ISR,
│                                    interrupt counter, interrupt LED)
├── lab_manual_04_context_switching.md <- Exp 24-40 (2/3/4 tasks, round robin,
│                                    priority, cooperative, timer/ext-interrupt
│                                    context switch, RTOS simulation,
│                                    ENHANCED mini-RTOS)
├── lab_manual_05_multifile.md    <- multi-file RTOS kernel project
├── lab_manual_06_application.md  <- Exp 41-44 (traffic light, water level,
│                                    counter, preemptive priority RTOS)
└── src/
    ├── mcu51.h                   <- portable header (in every folder too)
    ├── 01_basics/                <- exp01_led_on.c ... exp13_arithmetic_ops.c
    ├── 02_timers/                <- exp14 ... exp18
    ├── 03_interrupts/            <- exp19 ... exp23
    ├── 04_context_switching/     <- exp24 ... exp40
    ├── 05_multifile/             <- mcu51.h, tasks.h, task1.c, task2.c,
    │                                task3.c, scheduler.c, main.c
    └── 06_application/           <- exp41 ... exp44
```

## Quick start (any program)

1. Copy the folder that contains your program **and its `mcu51.h`** (e.g.
   `src/04_context_switching/`) to your lab machine.
2. In MCU 8051 IDE: **File → New project** → name it → OK.
3. **Project → Add files to project** → select your `.c` file (+ the rest of the
   files in `05_multifile/` if using the multi-file project).
4. Check the compiler is SDCC: **Configure → Compiler configuration → C language**.
5. **Project → Compile** (messages panel: *success*).
6. **Simulation → Run**, then open **Peripherals → Ports → Port 1** (and
   Port 0/2/3, Timer 0, Interrupts, Serial) and watch the outputs.

> Detailed, step-by-step instructions for every part are in
> `lab_manual_00_overview.md` (§ "How to run in MCU 8051 IDE").

## About mcu51.h (read this!)

MCU 8051 IDE compiles C with **SDCC**. Recent SDCC (3.9+) no longer accepts the
Keil keywords `sbit`, `interrupt` and `bit`. The header `mcu51.h` maps them
automatically:

| You want (Keil style)             | Portable form in these programs |
|-----------------------------------|----------------------------------|
| `sbit LED = P1^0;`                | `SBIT(LED, 0x90);`               |
| `void isr(void) interrupt 1 { }`  | `ISR(timer0_isr, 1) { }`         |
| `bit running = 0;`                | `BIT running = 0;`               |

`SBIT`'s second argument is the **bit address** of the pin (P1.0 = 0x90,
P3.2 = 0xB2, ... full table in the overview manual). On Keil the same macro
produces standard `sbit LED = 0x90;` code, so one source works on both compilers.

Every program `#include "mcu51.h"` and expects the header **in the same folder**.

## What you can say in the viva about this

- The 8051 has **no built-in RTOS** — context switching is simulated in software.
- A real RTOS saves the context = **PC, SP, A, B, PSW, R0-R7**, then the scheduler
  picks the next task and restores it.
- In these labs the "save/restore" is simulated with a **task variable / task table**
  (TCB arrays) and the switching point is a **function call, a delay, or the
  Timer0 tick interrupt**.
