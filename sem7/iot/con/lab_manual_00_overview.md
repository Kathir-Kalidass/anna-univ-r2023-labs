# Lab Manual — Part 00: Overview, Theory, How to Run in MCU 8051 IDE

## Contents of this part
1. What you must know before the lab (8051 basics)
2. Context Switching + RTOS concepts (theory + viva answers)
3. MCU 8051 IDE — full setup (SDCC + project + compiler config)
4. How to run ANY of the 44 programs, step by step
5. How to run the multi-file project
6. Keil vs SDCC syntax table + bit-address table
7. Timer reload values used in the manual
8. Common errors and fixes
9. Full viva question bank (with answers)

---

## 1. 8051 quick facts (memorise these)

| Item | Value |
|------|-------|
| Internal RAM | 128 bytes (00H-7FH), bit-addressable 20H-2FH |
| Special Function Registers (SFR) | 21 registers in 80H-FFH |
| Ports | P0 (0x80), P1 (0x90), P2 (0xA0), P3 (0xB0) — 8-bit each |
| Timers | Timer0, Timer1 — 16-bit, Modes 0,1,2,3 |
| Timer Mode 1 | 16-bit counter, max 65536 counts |
| Interrupts | INT0(0), Timer0(1), INT1(2), Timer1(3), Serial(4) |
| Machine cycle | 12 clock periods (1 µs at 12 MHz) |
| `EA = 1` | Master (global) interrupt enable |
| `ET0 = 1` | Enable Timer0 interrupt |
| `EX0/EX1 = 1` | Enable INT0/INT1 |
| `TR0 = 1` | Start (run) Timer0 |
| `TF0` | Timer0 overflow flag (auto-cleared when ISR runs) |

Timer0 Mode 1 load value for **~1 ms at 12 MHz**: `TH0 = 0xFC; TL0 = 0x66;`
(65536 - 64550 = 986 counts ≈ 1 ms). For other delays see section 7.

---

## 2. Context switching + RTOS theory (viva answers)

### 2.1 What is a task?
An independent function/unit of work that the CPU executes. Example: `Task1()` blinks
an LED, `Task2()` reads a switch.

### 2.2 What is a process?
A program in execution, with its own context (CPU state) and resources.

### 2.3 What is context?
The complete CPU state of a task that must be saved to resume it exactly:
**Program Counter (PC), Stack Pointer (SP), Accumulator (A), B register,
PSW (Program Status Word), general purpose registers R0-R7.**

### 2.4 What is context switching?
Saving the context of the currently running task and restoring the context of the
next task, so that many tasks appear to run concurrently (multitasking).

### 2.5 Why is context switching needed?
- To run multiple tasks (multitasking) on one CPU.
- To improve CPU utilisation.
- To let high-priority tasks run immediately.
- It is the heart of every RTOS.

### 2.6 What is a scheduler?
The part of the OS/RTOS that decides **which task runs next** and when.

### 2.7 Round Robin scheduling
Each task gets a fixed **time quantum**. When the quantum expires, the scheduler
switches to the next task in a circular order: Task1 → Task2 → Task3 → Task1 → ...

### 2.8 Priority scheduling
The READY task with the **highest priority** runs first. A higher-priority task can
**preempt** (interrupt) a lower-priority one.

### 2.9 Cooperative vs Preemptive scheduling
- **Cooperative:** a task runs until it *itself* gives up the CPU (yields).
- **Preemptive:** the scheduler (usually via a **timer interrupt**) forces a switch,
  even if the task is not finished.

### 2.10 Why is a Timer interrupt used for context switching?
A timer generates **periodic interrupts** (ticks). On each tick the ISR gives control
back to the scheduler, which can then decide to switch tasks. This is how an RTOS
implements preemptive multitasking.

### 2.11 What triggers a context switch?
- Timer overflow / tick interrupt
- External interrupt
- The scheduler itself (round-robin quantum expiry, priority change)
- A task finishing or waiting (yield / sleep)

### 2.12 Why save the Stack Pointer?
So that the task **resumes exactly where it stopped** — SP points to the saved return
address on the stack.

### 2.13 Difference: Interrupt vs Context Switch

| Interrupt | Context Switch |
|-----------|----------------|
| Temporarily stops current execution | Switches execution to another task |
| Returns to the same task | May resume a different task |
| Caused by hardware/software event | Managed by the scheduler |
| ISR executes | New task context restored |

### 2.14 Can the 8051 do context switching?
**Yes, in software.** The 8051 has no hardware support for task switching and no
built-in RTOS, so context switching is **simulated in Embedded C** by saving state in
variables/arrays and switching between task functions.

### 2.15 What is starvation?
A low-priority task never gets the CPU because higher-priority tasks are always ready.
(Can be cured with ageing, or by making high-priority tasks sleep/yield.)

### 2.16 What is latency?
Delay between an event occurring and the system reacting (e.g. interrupt latency =
time from interrupt request to ISR start).

### 2.17 What is a time quantum?
The fixed CPU time slice given to each task in round-robin scheduling.

### 2.18 Multitasking vs Multiprocessing
- **Multitasking:** one CPU switches between many tasks (time-sharing).
- **Multiprocessing:** many CPUs/cores run tasks in parallel.

### 2.19 Where would a real RTOS save the context?
On the task's own **stack** (a TCB per task stores PC, SP, A, B, PSW, R0-R7 and a
stack region). The scheduler swaps SP to the next task's stack.

---

## 3. MCU 8051 IDE — full setup

### 3.1 Install
1. Install **MCU 8051 IDE** (free, open source, Windows/Linux).
2. Install **SDCC** (Small Device C Compiler) — MCU 8051 IDE needs it for C files.
   - On Windows: run the SDCC installer and **tick "Add to PATH"**.
   - Check from a terminal: `sdcc -v` must print a version.
3. Start MCU 8051 IDE.

### 3.2 Create a project
1. **File → New project...**
2. Enter a project name (e.g. `context_switch`) and a location, click OK.
3. The project tree shows `Source files`.

### 3.3 Add a C file
1. Copy your `.c` file **and `mcu51.h`** into the project folder
   (both must be in the SAME folder).
2. **Project → Add files to project...** → select the `.c` file.
3. For the multi-file project (Part 5), add `task1.c`, `task2.c`, `task3.c`,
   `scheduler.c`, `main.c` (and keep `tasks.h` + `mcu51.h` in the folder).

### 3.4 Set the compiler
1. Main menu **Configure → Compiler configuration → C language**.
2. Make sure the compiler is **SDCC** (compiler executable `sdcc.exe` / `sdcc`).
3. Under **General**, you may set the C standard to **C99** (all code here is C89
   compatible, so either works).
4. Make sure **"--debug"** is ON so the simulator can single-step source lines
   (if you see *Unable to find "xxx.cdb"*, enable `--debug` here).

### 3.5 Compile
- Menu **Project → Compile** (or the compile button on the toolbar, or press **F7**).
- Watch the **Messages** panel. `0 errors` = success. Output files (.ihx/.hex/.sim)
  are written next to the project.

---

## 4. How to run ANY single-file program (step by step)

1. Open MCU 8051 IDE, create project (3.2), add the `.c` file + `mcu51.h` (3.3).
2. Compile (3.5). Fix any error first.
3. Start simulation: toolbar **Run** button or **Simulation → Run**.
   - Use **Step** to single-step and watch each instruction.
   - Use **Run** for continuous execution.
4. Open the peripheral windows (menu **Peripherals**):
   - **Ports → Port 0 / Port 1 / Port 2 / Port 3** — shows each pin as a checkbox
     (ticked = logic 1). This is how you **see the LED pattern** and **press switches**
     (click a P3.2 box to simulate a button press / interrupt).
   - **Timers/Counter 0** — shows TH0/TL0 counting and TF0. Useful for timer programs.
   - **Interrupts** — shows EA/ET0/EX0/IT0 and pending flags. Verify the ISR runs.
   - **Serial port** — the **terminal** window shows UART text (`T1`/`T2` in Exp 39).
5. For each experiment the manual says exactly which window to watch.

Example — Exp 29 (Timer0 context switch):
- Port 1 window: pins keep flipping between `0101 0101` (0x55) and `1010 1010` (0xAA).
- Timer 0 window: TH0/TL0 count up and reload each ~1 ms.
- Interrupts window: Timer0 interrupt fires repeatedly.

---

## 5. How to run the MULTI-FILE project (Part 5)

1. Copy the whole `src/05_multifile/` folder somewhere.
2. Create a project, add **all five** `.c` files (mcu51.h + tasks.h stay in folder).
3. Compile — MCU 8051 IDE compiles each file and links them automatically.
4. Run and open **Ports → Port 1 / Port 0 / Port 2**, **Timer 0**, **Interrupts**.
   - P1 alternates 0x55/0xAA (TaskLED), P0 counts (TaskCounter), P2 shows switch (TaskSwitch).
5. Toggle P3.2 in the Port 3 window to see TaskSwitch react.

---

## 6. Keil vs SDCC syntax + bit address table

`mcu51.h` lets you write one source that compiles on both. The raw differences:

| Meaning | Keil C51 | SDCC (3.9+) | This manual |
|---------|----------|-------------|-------------|
| bit of a port | `sbit LED = P1^0;` | `__sbit __at(0x90) LED;` | `SBIT(LED, 0x90);` |
| interrupt function | `void isr(void) interrupt 1 { }` | `void isr(void) __interrupt(1) { }` | `ISR(timer0_isr, 1) { }` |
| 1-bit variable | `bit b;` | `__bit b;` | `BIT b;` |
| SFR | `sfr P1 = 0x90;` | `__sfr __at(0x90) P1;` | (already in reg51.h) |

**Bit addresses you need** (second argument of `SBIT`):

| Pin | Addr | Pin | Addr | Pin | Addr | Pin | Addr |
|-----|------|-----|------|-----|------|-----|------|
| P0.0 | 0x80 | P1.0 | 0x90 | P2.0 | 0xA0 | P3.0 | 0xB0 |
| P0.1 | 0x81 | P1.1 | 0x91 | P2.1 | 0xA1 | P3.1 | 0xB1 |
| P0.2 | 0x82 | P1.2 | 0x92 | P2.2 | 0xA2 | P3.2 (INT0) | 0xB2 |
| P0.3 | 0x83 | P1.3 | 0x93 | P2.3 | 0xA3 | P3.3 (INT1) | 0xB3 |
| P0.4 | 0x84 | P1.4 | 0x94 | P2.4 | 0xA4 | P3.4 | 0xB4 |
| P0.5 | 0x85 | P1.5 | 0x95 | P2.5 | 0xA5 | P3.5 | 0xB5 |
| P0.6 | 0x86 | P1.6 | 0x96 | P2.6 | 0xA6 | P3.6 | 0xB6 |
| P0.7 | 0x87 | P1.7 | 0x97 | P2.7 | 0xA7 | P3.7 | 0xB7 |

---

## 7. Timer reload values used in this manual

At 12 MHz: 1 machine cycle = 1 µs. Timer Mode 1 (16-bit) counts 0 → 65535.

| Desired delay | Load value TH0,TL0 | Calculation |
|---------------|--------------------|-------------|
| ~1 ms   | `0xFC, 0x66` | 65536 - 64550 = 986 µs |
| ~5 ms   | `0xEC, 0x78` | 65536 - 5000   = 5 ms |
| ~50 ms  | `0x3C, 0xB0` | 65536 - 50000  = 50 ms |
| max     | `0x00, 0x00` | 65536 µs ≈ 65.5 ms |

For delays > 65 ms use a software loop around the 1 ms timer (see Exp 18).

---

## 8. Common errors and fixes

| Error | Reason | Fix |
|-------|--------|-----|
| `syntax error: token 'interrupt'` | SDCC 3.9+ does not accept `interrupt` keyword | use `ISR(name, n)` from mcu51.h |
| `syntax error: token 'sbit'` | same for `sbit` | use `SBIT(name, addr)` |
| `reg51.h not found` | compiler include path wrong | reinstall SDCC / check Configure → Compiler |
| `Unable to find "x.cdb"` | `--debug` switch disabled | Configure → Compiler config → enable `--debug` |
| `no sdcc compiler` at start | SDCC not on PATH | add SDCC bin folder to PATH, restart IDE |
| Program compiles but nothing happens | simulation not started / wrong port watched | Simulation → Run; open the right Port window |
| Interrupts never fire | `EA` not set, or interrupt window says disabled | set `EA=1`, `ET0=1` (or `EX0=1`) |
| LED pattern too fast to see | delay too short | increase delay loops (e.g. `i<300` → `i<1000`) |

---

## 9. Full viva question bank (with answers)

**Context switching / RTOS**
1. Define context switching. → See 2.4.
2. What is saved/restored in a context switch? → PC, SP, A, B, PSW, R0-R7 (2.3).
3. Why use a timer interrupt? → Periodic ticks let the scheduler preempt tasks (2.10).
4. What triggers a context switch? → Timer interrupt, external interrupt, scheduler (2.11).
5. Explain round robin. → 2.7. Explain priority scheduling. → 2.8.
6. Cooperative vs preemptive. → 2.9.
7. Task vs process. → 2.1, 2.2. What is a scheduler? → 2.6.
8. What is starvation? → 2.15. Latency? → 2.16. Time quantum? → 2.17.
9. Multitasking vs multiprocessing. → 2.18.
10. Can 8051 context switch? → 2.14.
11. Role of SP during switching. → 2.12.
12. Interrupt vs context switch. → 2.13.

**8051 / timers / interrupts**
13. How do you set Timer0 to 16-bit mode? → `TMOD = 0x01`.
14. Why reload TH0/TL0 inside the ISR? → Timer keeps giving the same period each tick.
15. Purpose of EA, ET0, EX0, TR0? → master enable, timer0 enable, INT0 enable, start timer.
16. What does `IT0 = 1` do? → INT0 is falling-edge triggered (instead of level).
17. Interrupt vector addresses? → INT0=0003H, T0=000BH, INT1=0013H, T1=001BH, serial=0023H.
18. Difference Timer vs Counter mode? → Timer counts machine cycles; counter counts
    external pulses on P3.4/T0 (Timer0 C/T bit).
19. What is a machine cycle? → 12 clock periods, 1 µs at 12 MHz.
20. Why does P0 need pull-ups? → P0 is open-drain; 8051 P0 has no internal pull-ups.

**Program-specific**
21. Why is `while(1);` empty in ISR programs? → The CPU is free; interrupts drive the system.
22. What do 0x55 and 0xAA mean? → alternate-bit patterns `01010101` / `10101010`.
23. Why debounce a switch? → Mechanical bouncing can count one press as many.
24. How many tasks in Exp 24/25/32? → 2 / 3 / 4.
25. How would a real RTOS differ? → Real RTOS stores real register/stack context and
    restores it; here we simulate switching with variables/functions.

---

*Next: Part 01 (lab_manual_01_basics.md) — Experiments 1-13.*
