# Lab Manual — Part 03: Interrupts (Exp 19-23)

Interrupt vectors on the 8051:

| Interrupt | Vector | Enable bit | Flag | Trigger pin |
|-----------|--------|-----------|------|-------------|
| INT0 (external 0) | 0003H | EX0 | IE0 | P3.2 |
| Timer0 overflow    | 000BH | ET0 | TF0 | internal |
| INT1 (external 1) | 0013H | EX1 | IE1 | P3.3 |
| Timer1 overflow    | 001BH | ET1 | TF1 | internal |
| Serial (RI/TI)     | 0023H | ES  | RI/TI | internal |

In the simulator use **Peripherals → Interrupts** to watch the enable bits and flags,
and **Ports → Port 3** to toggle P3.2/P3.3 (click the pin) to trigger external
interrupts.

---

## Experiment 19 — External interrupt INT0 toggles LED

**Aim:** Every falling edge on P3.2 (INT0) toggles P1.0.
**File:** `src/03_interrupts/exp19_external_int0.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

ISR(ext0_isr, 0)
{
    LED = !LED;
}

void main(void)
{
    EA  = 1;   /* enable global interrupts */
    EX0 = 1;   /* enable INT0             */
    IT0 = 1;   /* edge triggered          */

    while(1);  /* wait for interrupts     */
}
```

**How to test:** in the Port 3 window, click P3.2 twice (set → clear → set...). The LED
on P1.0 toggles on each falling edge.
**Explanation:** `IT0=1` selects falling-edge triggering (without it INT0 is
level-triggered). The ISR `ISR(ext0_isr,0)` serves vector 0.
**Result:** External interrupt INT0 executed successfully.
**Viva:** Difference IT0=0 vs IT0=1? → Level vs falling-edge triggering.

---

## Experiment 20 — External interrupt INT1 toggles all P1 LEDs

**File:** `src/03_interrupts/exp20_external_int1.c`
```c
#include "mcu51.h"

ISR(ext1_isr, 2)
{
    P1 = ~P1;   /* toggle all LEDs */
}

void main(void)
{
    EA  = 1;
    EX1 = 1;    /* enable INT1 */
    IT1 = 1;    /* falling edge triggered */

    while(1);
}
```

**How to test:** toggle P3.3 in the Port 3 window. **Output:** all 8 LEDs on P1 flip.
**Result:** INT1 program executed successfully.
**Viva:** INT1 is on which pin? → P3.3, vector 0013H, interrupt number 2.

---

## Experiment 21 — Timer0 overflow counter

**Aim:** Count Timer0 overflows and display the count on P1.
**File:** `src/03_interrupts/exp21_timer0_counter.c`
```c
#include "mcu51.h"

unsigned char overflows = 0;

ISR(timer0_isr, 1)
{
    overflows++;             /* count each overflow  */
    P1 = overflows;          /* display count        */

    TH0 = 0xFC;              /* reload for 1 ms      */
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

**Output:** P1 counts 1,2,3,... (≈ every 1 ms). **Result:** Executed successfully.
**Viva:** Why does `overflows` need to be global? → ISR and main share it; a local
variable would be destroyed after the ISR returns.

---

## Experiment 22 — Interrupt counter (count INT0 presses)

**File:** `src/03_interrupts/exp22_interrupt_counter.c`
```c
#include "mcu51.h"

unsigned char count = 0;

ISR(ext0_isr, 0)
{
    count++;
    P1 = count;   /* show count in binary */
}

void main(void)
{
    EA  = 1;
    EX0 = 1;
    IT0 = 1;      /* falling edge triggered */

    while(1);
}
```

**Output:** each press of P3.2 increments the count shown on P1 (1,2,3,...0xFF→0).
**Result:** Executed successfully. **Modification:** compare with Exp 11 (polling) —
with interrupts the main loop is free.

---

## Experiment 23 — Interrupt controlled LED (INT0 starts/stops blink)

**Aim:** INT0 toggles a "running" flag that starts/stops a Timer0-driven blink.
**File:** `src/03_interrupts/exp23_interrupt_controlled_led.c`
```c
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */
BIT running = 0;   /* 0 = stopped, 1 = running */

ISR(ext0_isr, 0)
{
    running = !running;      /* start / stop blinking */

    if(running)
        TR0 = 1;             /* start timer */
    else
    {
        TR0 = 0;             /* stop timer  */
        LED = 1;             /* LED OFF     */
    }
}

ISR(timer0_isr, 1)
{
    LED = !LED;

    TH0 = 0xFC;
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;       /* timer interrupt   */
    EX0 = 1;       /* INT0 interrupt    */
    EA  = 1;
    IT0 = 1;

    while(1);
}
```

**Explanation:** Two ISRs share the CPU. INT0 toggles `running` and controls TR0; the
Timer0 ISR blinks. This is a tiny example of **event-driven behaviour**, and the two
interrupts "take turns" — conceptually close to context switching.
**Output:** press P3.2 → blink starts; press again → blink stops.
**Result:** Executed successfully.
**Viva:** What type is `running`? → a 1-bit flag (Keil `bit` / SDCC `__bit`), written here
as `BIT running`.

---

*Next: Part 04 (lab_manual_04_context_switching.md) — Experiments 24-40.*
