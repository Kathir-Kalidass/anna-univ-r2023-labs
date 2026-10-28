# Lab-2 / Lab-3 Context Switching — MCU 8051 IDE + SDCC

All 42 programs in this folder are written **in context-switch mode only**.
Every exercise is split into two or more **tasks**, and the CPU context
(ACC, B, PSW, SP, DPTR, R0-R7, task variables) is **saved and restored**
around every switch.

## Folder contents

| File | Lab exercise | Tasks |
|------|-------------|-------|
| `ex01_arithmetic_choice_tasks.c` | Lab-2 #1 arithmetic (choice 1-5) | Add / Sub / Mul / Div / Exit |
| `ex02_count_ones.c` | Lab-2 #2 count 1's | read number, count set bits |
| `ex03_countdown_timer.c` | Lab-2 #3 countdown 10->0 | countdown, 1 s delay |
| `ex04_16bit_arithmetic.c` | Lab-2 #4 16-bit add/sub | read, ADD, SUB |
| `ex05_led_motor_bitram.c` | Lab-2 #5 LED+motor (bit RAM) | LED, motor |
| `ex06_reverse_array_stack.c` | Lab-2 #6 reverse array (PUSH/POP) | push, pop, display |
| `ex07_register_banks.c` | Lab-2 #7 register banks | 4 bank-switch tasks |
| `ex08_cpu_register_monitor.c` | Lab-2 #8 read CPU regs | capture, display |
| `ex09_round_robin.c` | Lab-2 #9 round-robin | LED pattern, switch, counter |
| `ex10_cooperative_yield.c` | Lab-2 #10 cooperative | pattern, switch, arithmetic |
| `ex11_timer_interrupt_switch.c` | Lab-2 #11 timer ISR switch | blink, switch, rotate |
| `ex12_external_interrupt_switch.c` | Lab-2 #12 ext. INT0 switch | background, ISR |
| `ex13_producer_consumer.c` | Lab-2 #13 producer-consumer | produce, consume |
| `ex14_separate_stacks.c` | Lab-2 #14 separate stacks | 3 tasks, own SP each |
| `ex15_switch_aa55.c` | Lab-3 #1 switch -> AA/55H | monitor switch, display |
| `ex16_complement_number.c` | Lab-3 #3 complement | read, complement |
| `ex17_left_rotate.c` | Lab-3 #4 left rotate | rotate, display, delay |
| `ex18_circular_led_pattern.c` | Lab-3 #5 circular LED | rotate, delay |
| `ex19_data_serialization.c` | Lab-3 #6 serialize A5H | serialize, bit-delay |
| `ex20_compare_two_numbers.c` | Lab-3 #8 compare (3 tasks) | read A, read B, compare |
| `ex21_even_odd_detect.c` | Lab-3 #9 even/odd | read, detect |
| `ex22_bit_status_detect.c` | Lab-3 #10 bit status | read, check bit 3 |
| `ex23_timer_1s_blink_counter.c` | Lab-3 #11 timer blink+counter | blink, count |
| `ex24_traffic_light_tasks.c` | Lab-3 #12 traffic light | Green, Yellow, Red, Timing |
| `ex25_timer_round_robin.c` | Lab-3 #14 timer RR (3 tasks) | blink, switch, rotate |
| `ex26_register_banks_3tasks.c` | Lab-3 #15 register banks | 3 bank tasks, PSW save/restore |
| `ex27_setup_demo_blink_counter.c` | Lab-3 #16 setup demo | blink, counter |
| `ex28_alu8bit_tasks.c` | Lab-2 Act #1 8-bit ALU | 12 op tasks (ADD..SETB) |
| `ex29_alu16bit_tasks.c` | Lab-2 Act #2 16-bit ALU | add, sub, mul, div |
| `ex30_bit_addressable_ram.c` | Lab-2 Act #3 bit RAM | set bitA, toggle bitB, echo |
| `ex31_stack_push_pop.c` | Lab-2 Act #4 PUSH/POP | push, pop, verify LIFO |
| `ex32_sfr_access_tasks.c` | Lab-2 Act #6 SFR 80H-FFH | read, store, display |
| `ex33_loop_jump_subroutine.c` | Lab-2 Act #7 loops/jumps/sub | loop, jump, subroutine |
| `ex34_port_monitoring.c` | Lab-3 #2 port monitoring | read switches, display |
| `ex35_complement_8bit.c` | Lab-3 #7 complement 8-bit | read, complement (save/restore ACC/B/PSW) |
| `ex36_cooperative_3task.c` | Lab-3 #13 cooperative (3 tasks) | pattern, switch, counter |
| `ex37_psw_management.c` | Lab-2 Act #5 PSW management | 3 banks, PSW save/restore |
| `ex38_timer_cs.c` | Lab-2 Act #8 timer-based CS | blink, counter, port monitor |
| `ex39_register_bank_4.c` | Lab-2 Act #9 register banks | 4 banks (0-3), PSW switch |
| `ex40_cooperative_calc.c` | Lab-2 Act #10 cooperative | pattern, switch, arithmetic |
| `ex41_preemptive_cs.c` | Lab-2 Act #11 preemptive CS | save/restore ACC,B,PSW,SP,DPTR |
| `ex42_full_cs_demo.c` | Lab-2 Act #12 full CS demo | blink, arithmetic, port, counter |

`mcu51.h` — portable header. It lets the same code compile on **SDCC**
(M CU 8051 IDE's compiler) and **Keil C51**. Modern SDCC rejects Keil
keywords `sbit`, `interrupt`, `bit`, so they are mapped to macros:
`SBIT(name,addr)`, `ISR(name,vector)`, `BIT`, `AT_DATA`, `SBIT_RAM`.

## Exercise coverage (all four lists)

| List | Exercises | Files |
|------|-----------|-------|
| Lab-2 Context Switching (1-14) | `ex01`-`ex14` | 14 |
| Lab-3 Context Switching (1-16) | `ex15`-`ex27`, `ex34`-`ex36` | 16 |
| Lab-2 Context-Switching Activities (1-12) | `ex28`-`ex33`, `ex37`-`ex42` | 12 |
| Lab-2 original (1-8, non-CS basis) | covered in context-switch form by Lab-2 CS #1-8 (`ex01`-`ex08`) | — |

Total: **42 programs**. (The four lists sum to 42 exercises, not 69 - the
original Lab-2 exercises 1-8 are the pre-context-switching versions that
Lab-2 CS #1-8 restructure into tasks. Plain non-CS versions of those 8 are
also available in `../src/01_basics/` from the earlier package.)

## How to run (MCU 8051 IDE)

1. Open **MCU 8051 IDE**.
2. **Project -> New project** (name it, e.g. `ex24_traffic_light`).
3. **Project -> Add files...** -> add `mcu51.h` AND the exercise `.c` file.
4. **Project -> Configure** (or right-click the .c in the project tree):
   - Compiler: **SDCC**
   - Chip: **AT89C52** (or AT89C51)
5. **Project -> Compile** (F7). Status bar shows `0 Errors, 0 Warnings`.
6. **Simulation -> Start** (or the green Run button).
7. **Peripherals -> Port 1**, **Port 0**, **Port 2**, **Port 3** windows
   open; watch LEDs toggle. For exercises with switches (P3.x) click the
   pins in the **P3** window or in the chip view to press/release them.
8. For timer exercises (`ex11`, `ex23`, `ex24`, `ex25`) open
   **Peripherals -> Timer 0** to watch the tick; the ISR switches tasks.

### Command-line (optional, same compiler as the IDE)

```sh
sdcc -mmcs51 --out-fmt-ihx --code-size 0x8000 --iram-size 256 \
     --xram-size 0 --nooverlay --noinduction --model-small ex24_traffic_light_tasks.c
```

Produces `ex24_traffic_light_tasks.ihx` (load into the simulator).

## Context-switching ideas to explain in viva

- **Software (cooperative)** — tasks run to completion / one step and
  return; scheduler in `main()` picks the next (`ex01-ex10`, `ex15-ex22`).
- **Preemptive (timer ISR)** — Timer0 interrupt fires every ~5 ms and
  switches `current` in the ISR, interrupting any task (`ex11`, `ex23-ex25`).
- **Hardware context save (external INT0)** — CPU pushes PC+PSW on the
  stack before the ISR and restores them on RETI (`ex12`).
- **Register banks** — RS0/RS1 bits of PSW select bank 0..3, each task
  owns a bank (`ex07`, `ex26`).
- **Separate stacks** — each task has its own stack; SP (SFR 0x81) is
  saved/restored in the task's control block (`ex14`).
- **Synchronisation** — producer/consumer with buffer + `count`
  (`ex13`); traffic-light phase counter (`ex24`).
