# Lab 4 — 8051 Embedded C practical pack

This folder contains **81 standalone 8051 C programs** for MCU 8051 IDE / SDCC. Build **exactly one `.c` file per project**: each program has its own `main()`. The comprehensive prompt-to-source mapping is in [FULL_QUESTION_INDEX.md](FULL_QUESTION_INDEX.md).

## Correct wiring (11.0592 MHz crystal)

| Device | Pin(s) | Simulator / hardware note |
|---|---|---|
| LEDs | P1.0–P1.7 | Active-high in this pack; view Port 1. |
| Switch bank | P0.0–P0.7 | Active-low; fit pull-ups in hardware, or change Port 0 bits in the simulator. |
| External interrupt INT0 | P3.2 | Use a falling edge for INT0 programs. |
| Counter T0 | P3.4 | Use rising external pulses for counter-mode programs. |
| UART | RXD=P3.0, TXD=P3.1 | 9600 baud, 8N1. |
| LCD (8-bit) | D0–D7=P2.0–P2.7, RS=P3.4, EN=P3.5, RW=GND | Used by sources including `lab4_common.h`. |

> **Resource conflict:** Counter T0 and LCD RS both use P3.4. They work correctly as separate experiments, but do not connect/use the LCD and T0 counter at the same time. UART does not conflict with the LCD wiring in this pack.

## Build and simulate

1. Create an AT89C51 or AT89C52 project in MCU 8051 IDE.
2. Set crystal frequency to **11.0592 MHz** and select the SDCC compiler.
3. Add one required `.c` source only. Keep `mcu51.h` and `lab4_common.h` alongside it.
4. Build with F9, load the generated `.ihx`, and run with F5.
5. Open the relevant peripheral: Port 1/2/3 for LEDs and inputs, Timers for timer/counter programs, Serial Terminal for UART, and the LCD peripheral if the simulator offers it.

All 81 sources compile with SDCC 4.2.0. SDCC may show a `reg51.h` deprecation message while falling back to `8052.h`; this is a toolchain header notice, not a program error.

## Choose the right file

| Topic | Recommended files |
|---|---|
| GPIO and switch basics | `01_gpio_blink.c` through `07_switch_press_counter.c`, `31_gpio_all_leds_toggle.c`, `32_gpio_door_lock.c`, `33_long_short_press.c` |
| Timers / counters | `08_timer0_blink_polling.c` through `13_counter_visitor_int0.c`, `34_timer_warning_flash.c` through `38_lcd_countdown.c`, `50_timer_sensor_scheduler.c` |
| UART | `14_uart_send_hello.c`, `15_uart_receive_echo.c`, `16_uart_command_led.c`, `17_uart_serial_interrupt.c`, `43_uart_send_switch.c` through `47_uart_bluetooth_led.c` |
| LCD | `18_lcd_hello.c` through `22_uart_to_lcd.c`, `37_lcd_stopwatch.c` through `42_lcd_scroll_right.c` |
| Interrupts | `09_timer0_interrupt_blink.c`, `23_external_interrupt_toggle.c`, `24_emergency_stop.c`, `48_interrupt_priority.c`, `49_interrupt_count.c` |
| Stack / context-switching | `27_stack_push_pop.c`, `28_round_robin_tasks.c`, `29_timer_task_switch.c`, `30_stack_context_notes.md` |
| Integrated application | `25_traffic_signal_timer.c`, `26_timer_uart_lcd_gpio.c`, `50_timer_sensor_scheduler.c` |

Several older and newer files demonstrate the same concept (for example, multiple Timer0-blink, LCD-HELLO and UART-command programs). They are retained deliberately as alternative working answers; choose the descriptive filename above rather than relying on its number.

## Expected output

- GPIO, timer, counter, interrupt and task demos: changing Port 1 / Port 2 / Port 3 values.
- UART demos: text and command responses in the 9600 8N1 serial terminal.
- LCD demos: text on the configured 16×2 LCD peripheral; visual support depends on the MCU 8051 IDE installation.
- Stack demos: inspect `SP`, `ACC`, and Port 1 in the Watch/SFR windows.

## Viva facts

- `SBUF` carries serial bytes; clear `TI` after polled transmit and `RI` after receive.
- `TR0`/`TR1` starts a timer; `TF0`/`TF1` indicates overflow.
- `EA=0` disables maskable interrupts. End an ISR with `RETI`, not `RET`.
- Timer mode counts internal machine cycles; counter mode counts transitions at T0/T1.
- Timer1 Mode 2 with `TH1=FDH` provides 9600 baud at 11.0592 MHz.
