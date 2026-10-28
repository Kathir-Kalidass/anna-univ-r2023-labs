# Lab Manual — Part 01: Embedded C Basics (Exp 1-13)

Common setup for all experiments:
- `mcu51.h` must be in the same folder as the `.c` file (portable SDCC/Keil header).
- LEDs are active-low on the lab board (0 = ON, 1 = OFF) unless stated otherwise.
- Watch the output in **Peripherals → Ports → Port 1**.

---

## Experiment 1 — Turn ON all LEDs

**Aim:** Display 0x00 on Port 1 so all 8 LEDs glow.
**Algorithm:**
1. Load P1 with 0x00.
2. Stay in an infinite loop so LEDs remain ON.

**File:** `src/01_basics/exp01_led_on.c`

```c
/* Experiment 1 : Turn ON all LEDs on Port 1 */
#include "mcu51.h"

void main(void)
{
    P1 = 0x00;   /* 00000000b -> all LEDs ON (active-low LEDs) */
    while(1);    /* keep LEDs ON forever */
}
```

**Explanation:** `P1 = 0x00` writes all zeroes to Port 1 → all LEDs ON. The `while(1);`
holds the program so the pattern is not lost.
**Output:** All 8 LEDs ON.
**Result:** LED ON program executed successfully.
**Viva:** Why active low? → The board connects each LED from Vcc through the port pin;
a 0 pulls the cathode low and lights it.
**Modification:** Make P1=0xFF to switch them OFF (Exp 2).

---

## Experiment 2 — Turn OFF all LEDs

```c
/* Experiment 2 : Turn OFF all LEDs on Port 1 */
#include "mcu51.h"

void main(void)
{
    P1 = 0xFF;   /* 11111111b -> all LEDs OFF */
    while(1);
}
```

**Output:** All 8 LEDs OFF. **Result:** LED OFF program executed successfully.

---

## Experiment 3 — Blink all LEDs

**Aim:** Toggle all LEDs ON and OFF continuously.
**File:** `src/01_basics/exp03_led_blink.c`

```c
/* Experiment 3 : Blink all LEDs on Port 1 */
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    while(1)
    {
        P1 = 0x00;   /* LEDs ON  */
        delay();     /* wait */
        P1 = 0xFF;   /* LEDs OFF */
        delay();     /* wait */
    }
}
```

**Explanation:** The nested `for` loop wastes machine cycles → delay (~half second).
P1 alternates 0x00 and 0xFF so all LEDs blink together.
**Output:** All LEDs blink ON-OFF-ON-OFF repeatedly.
**Result:** Blink program executed successfully.
**Viva:** Can we use a timer instead of a software delay? → Yes, see Exp 14-16
(timer uses hardware, so CPU is free).

---

## Experiment 4 — Alternate LED pattern

**File:** `src/01_basics/exp04_alternate_led.c`
```c
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 400; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    while(1)
    {
        P1 = 0x55;   /* 0101 0101 */
        delay();
        P1 = 0xAA;   /* 1010 1010 */
        delay();
    }
}
```

**Explanation:** 0x55 = 01010101 and 0xAA = 10101010 are complementary patterns, so
alternate LEDs switch on/off in opposite phase.
**Output:** 0x55 → 0xAA → 0x55 → ... **Result:** Executed successfully.
**Viva:** What is the relation between 0x55 and 0xAA? → 0xAA = ~0x55 (complement).

---

## Experiment 5 — Running LED (Left shift)

**File:** `src/01_basics/exp05_running_led_left.c`
```c
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    unsigned char x = 0x01;   /* start at bit0 */

    while(1)
    {
        P1 = x;
        delay();
        x = x << 1;           /* shift left */

        if(x == 0)            /* after bit7 falls off, wrap */
            x = 0x01;
    }
}
```

**Dry run:** x = 00000001 → 00000010 → 00000100 → ... → 10000000 → (shift gives 0) → 00000001.
**Output:** A single LED runs from left to right (bit0 → bit7).
**Result:** Executed successfully.
**Viva:** Why the `if(x==0)` check? → After bit7, a left shift produces 0; we reload 0x01
to make the pattern repeat.

---

## Experiment 6 — Running LED (Right shift)

**File:** `src/01_basics/exp06_running_led_right.c` — identical structure with `x=0x80`,
`x = x >> 1`, reload to 0x80.
**Output:** LED runs from bit7 → bit0. **Result:** Executed successfully.

---

## Experiment 7 — LED chase pattern (array)

**File:** `src/01_basics/exp07_led_chase.c`
```c
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 250; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    unsigned char k;
    unsigned char pattern[8] = {0x01, 0x02, 0x04, 0x08,
                                0x10, 0x20, 0x40, 0x80};

    while(1)
    {
        for(k = 0; k < 8; k++)
        {
            P1 = pattern[k];
            delay();
        }
    }
}
```

**Explanation:** `pattern[]` stores 8 single-bit patterns; a `for` loop outputs each with
a delay → chasing LED. **Output:** One LED lights in sequence 1,2,4,8,16,32,64,128.
**Result:** Executed successfully. **Modification:** reverse the array for a backward chase.

---

## Experiment 8 — Read Port 0 and display on Port 1

**File:** `src/01_basics/exp08_port_copy.c`
```c
#include "mcu51.h"

void main(void)
{
    while(1)
    {
        P1 = P0;   /* copy P0 (input) to P1 (LED) */
    }
}
```

**In simulator:** set the P0 pattern in **Peripherals → Ports → Port 0**, and the same
pattern appears on P1.
**Output:** Whatever is on P0 is mirrored to P1. **Result:** Executed successfully.
**Viva:** Port 0 on real hardware needs pull-up resistors to read input.

---

## Experiment 9 — Switch controls LED

**File:** `src/01_basics/exp09_switch_controls_led.c`
```c
#include "mcu51.h"

SBIT(SW,  0xB2);   /* P3.2 */
SBIT(LED, 0x90);   /* P1.0 */

void main(void)
{
    while(1)
    {
        if(SW == 0)
            LED = 0;   /* pressed  -> LED ON  */
        else
            LED = 1;   /* released -> LED OFF */
    }
}
```

**Explanation:** `SBIT` creates a single-bit variable for P3.2 (switch) and P1.0 (LED).
A pressed switch reads 0 on many boards, so `SW==0` lights the LED.
**In simulator:** click P3.2 in the Port 3 window → P1.0 in Port 1 toggles.
**Result:** Executed successfully.

---

## Experiment 10 — Toggle LED on every press (debounced)

**File:** `src/01_basics/exp10_toggle_on_press.c`
```c
#include "mcu51.h"

SBIT(SW,  0xB2);   /* P3.2 */
SBIT(LED, 0x90);   /* P1.0 */

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 30; i++)
        for(j = 0; j < 1275; j++);   /* ~10 ms debounce */
}

void main(void)
{
    LED = 1;

    while(1)
    {
        if(SW == 0)              /* pressed ? */
        {
            delay();             /* debounce */

            if(SW == 0)          /* confirm still pressed */
            {
                LED = !LED;      /* toggle LED */

                while(SW == 0);  /* wait for release */
            }
        }
    }
}
```

**Explanation:** Debounce = two checks with a delay in between, so switch bounce is
filtered. `while(SW==0);` waits for release so one press = one toggle.
**Output:** Each single press flips the LED. **Result:** Executed successfully.
**Viva:** Why debounce? → Mechanical contacts bounce for a few ms and would count
several times.

---

## Experiment 11 — Count button presses

**File:** `src/01_basics/exp11_button_counter.c`
```c
#include "mcu51.h"

SBIT(SW, 0xB2);   /* P3.2 */

unsigned char count = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 20; i++)
        for(j = 0; j < 1275; j++);   /* debounce */
}

void main(void)
{
    while(1)
    {
        if(SW == 0)
        {
            delay();

            if(SW == 0)
            {
                count++;
                P1 = count;          /* display count in binary */

                while(SW == 0);      /* wait for release */
            }
        }
    }
}
```

**Output:** Every press increments `count`; P1 shows it in binary (1,2,3...).
**Result:** Executed successfully. **Modification:** clear count at 255 or display BCD.

---

## Experiment 12 — Bitwise operations

**File:** `src/01_basics/exp12_bitwise_ops.c`
```c
#include "mcu51.h"

void main(void)
{
    unsigned char a = 0x0F;   /* 0000 1111 */
    unsigned char b = 0x33;   /* 0011 0011 */

    while(1)
    {
        P1 = a & b;   /* AND  = 0x03  (0000 0011) */
        P2 = a | b;   /* OR   = 0x3F  (0011 1111) */
        P3 = a ^ b;   /* XOR  = 0x3C  (0011 1100) */
        P0 = ~a;      /* NOT  = 0xF0  (1111 0000) */
    }
}
```

**Dry run:**
- a & b: 00001111 AND 00110011 = 00000011 = 0x03
- a | b: 00111111 = 0x3F
- a ^ b: 00111100 = 0x3C
- ~a:    11110000 = 0xF0

**Result:** Executed successfully. **Viva:** What is XOR used for? → toggling bits
without affecting others; `x ^ mask` flips the masked bits.

---

## Experiment 13 — Arithmetic operations

**File:** `src/01_basics/exp13_arithmetic_ops.c`
```c
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 200; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    unsigned char x = 25, y = 10;

    while(1)
    {
        P1 = x + y;   /* 25+10 = 35   = 0x23 */
        delay();
        P1 = x - y;   /* 25-10 = 15   = 0x0F */
        delay();
        P1 = x * y;   /* 25*10 = 250  = 0xFA */
        delay();
        P1 = x / y;   /* 25/10 = 2    = 0x02 */
        delay();
        P1 = x % y;   /* 25%10 = 5    = 0x05 */
        delay();
    }
}
```

**Output:** P1 shows 0x23, 0x0F, 0xFA, 0x02, 0x05 in sequence.
**Result:** Executed successfully. **Viva:** Why does the product wrap? → 8-bit result,
250 fits but 256+ would overflow (mod 256).

---

*Next: Part 02 (lab_manual_02_timers.md) — Experiments 14-18.*
