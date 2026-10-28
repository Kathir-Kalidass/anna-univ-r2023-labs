# Lab Manual — Part 02: Timers (Exp 14-18)

Theory: The 8051 has two 16-bit timers (Timer0, Timer1). In **Mode 1** each is a 16-bit
up-counter from a loaded value up to FFFFH (65535); on overflow it sets flag TF0/TF1.
At 12 MHz one machine cycle = 1 µs, so loading `TH0/TL0 = 0xFC66` (65536−64550=986)
gives ~1 ms.

Watch in the simulator: **Peripherals → Timers/Counter 0** and **Ports → Port 1**.

---

## Experiment 14 — Timer0 delay (polling) + blink

**Aim:** Create a ~1 ms delay with Timer0 Mode 1 by polling TF0, and blink an LED.
**Algorithm:**
1. Set Timer0 Mode 1 (`TMOD=0x01`).
2. Load TH0=0xFC, TL0=0x66.
3. Start timer (TR0=1). Wait until TF0=1 (overflow).
4. Stop timer, clear flag. Toggle LED and repeat.

**File:** `src/02_timers/exp14_timer0_delay.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

void delay_1ms(void)
{
    TMOD = 0x01;     /* Timer0, Mode 1 (16-bit) */

    TH0 = 0xFC;
    TL0 = 0x66;      /* load count for ~1 ms */

    TR0 = 1;         /* start Timer0 */

    while(TF0 == 0); /* wait for overflow flag */

    TR0 = 0;         /* stop timer  */
    TF0 = 0;         /* clear flag  */
}

void main(void)
{
    while(1)
    {
        LED = !LED;
        delay_1ms();
    }
}
```

**Explanation:** Polling = the CPU waits (`while(TF0==0)`) inside `delay_1ms`, so it
cannot do other work (compare Exp 16 where the interrupt frees the CPU).
**Output:** LED blinks ~500 times/second (too fast — increase the loop or reload a bigger
delay to see it).
**Result:** Timer0 polling delay executed successfully.
**Viva:** What is polling? → Continuously checking a flag (TF0) in a loop. Drawback: CPU
is blocked.

---

## Experiment 15 — Timer1 delay (polling)

**File:** `src/02_timers/exp15_timer1_delay.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

void delay_1ms_timer1(void)
{
    TMOD = 0x10;     /* Timer1, Mode 1 (16-bit) */

    TH1 = 0xFC;
    TL1 = 0x66;

    TR1 = 1;         /* start Timer1 */

    while(TF1 == 0); /* wait for overflow */

    TR1 = 0;
    TF1 = 0;
}

void main(void)
{
    while(1)
    {
        LED = !LED;
        delay_1ms_timer1();
    }
}
```

**Explanation:** Identical to Exp 14 but uses Timer1 (TMOD low nibble 0 → Timer0;
high nibble 1 → Timer1). Registers TH1/TL1/TR1/TF1.
**Result:** Timer1 polling delay executed successfully.
**Viva:** What is `TMOD=0x10`? → low nibble 0000 (Timer0 mode 0) and high nibble 0001
(Timer1 mode 1).

---

## Experiment 16 — Blink LED using Timer0 INTERRUPT

**Aim:** Use Timer0 overflow interrupt so the CPU is free while the LED blinks.
**File:** `src/02_timers/exp16_blink_timer0_isr.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

ISR(timer0_isr, 1)
{
    LED = !LED;      /* toggle LED  */

    TH0 = 0xFC;      /* reload timer */
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;     /* Timer0 Mode 1 */

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;         /* enable Timer0 interrupt */
    EA  = 1;         /* enable global interrupt */

    TR0 = 1;         /* start Timer0 */

    while(1);        /* main does nothing */
}
```

**Explanation:** `ISR(timer0_isr,1)` declares an ISR for interrupt vector 1 (Timer0).
Every ~1 ms the ISR toggles the LED and reloads the timer. `while(1);` keeps main alive;
the CPU is otherwise free — the basis of **interrupt-driven context switching** (Exp 29).
**Output:** LED blinks continuously. **Result:** Executed successfully.
**Viva:** Why reload TH0/TL0 inside the ISR? → Without reload the timer would count from
0000H each time (full 65.5 ms period); reload keeps the ~1 ms period constant.
**Viva:** Purpose of EA=1? → Master switch; without it no interrupt is serviced.

---

## Experiment 17 — Square wave generation (Timer0 ISR)

**File:** `src/02_timers/exp17_square_wave.c`
```c
#include "mcu51.h"

SBIT(OUT, 0x90);   /* P1.0 */

ISR(timer0_isr, 1)
{
    OUT = !OUT;      /* toggle -> one half period per overflow */

    TH0 = 0xFC;
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;
    EA  = 1;

    TR0 = 1;

    while(1);
}
```

**Explanation:** Toggling the pin each ~1 ms gives a square wave of period ~2 ms
(frequency ≈ 500 Hz, 50% duty cycle).
**Output:** Square wave on P1.0 (see it flipping in the Port 1 window, or on an
oscilloscope on hardware). **Result:** Executed successfully.
**Viva:** What is duty cycle? → ON-time fraction of the period; here 50%.

---

## Experiment 18 — Multiple delays (5/20/50 ms) with Timer0

**File:** `src/02_timers/exp18_multi_delay.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

void timer_delay(unsigned int ms)
{
    unsigned int k;

    for(k = 0; k < ms; k++)      /* repeat ms times */
    {
        TMOD = 0x01;             /* Timer0 Mode 1 */

        TH0 = 0xFC;
        TL0 = 0x66;              /* ~1 ms load */

        TR0 = 1;

        while(TF0 == 0);         /* wait for overflow */

        TR0 = 0;
        TF0 = 0;
    }
}

void main(void)
{
    while(1)
    {
        LED = 0;   timer_delay(50);   /* ON  50 ms  */
        LED = 1;   timer_delay(20);   /* OFF 20 ms  */
        LED = 0;   timer_delay(5);    /* ON   5 ms  */
        LED = 1;   timer_delay(20);   /* OFF 20 ms  */
    }
}
```

**Explanation:** `timer_delay(ms)` loops the ~1 ms routine `ms` times, giving any
multiple of 1 ms (max 65 ms per timer load; longer delays need this loop).
**Output:** LED blinks with a 50-20-5-20 ms on/off sequence.
**Result:** Multi-delay program executed successfully.
**Viva:** How to make a 1 s delay? → call `timer_delay(1000)` (software loop around timer).

---

*Next: Part 03 (lab_manual_03_interrupts.md) — Experiments 19-23.*
