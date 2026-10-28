8051 Counter 0 — Mode 1 (16-bit)
Aim: To count external pulses arriving at pin T0 (P3.4) using Counter 0 in Mode 1 and display TH0 on Port 2 and TL0 on Port 1.
1. Corrected program for MCU 8051 IDE (SDCC)
Your textbook uses Keil syntax (reg51.h). Since your simulator uses SDCC, use this version:
#include <8051.h>

void main(void)
{
    T0 = 1;        /* Configure T0/P3.4 as input */
    TMOD = 0x05;   /* Counter 0, Mode 1 (16-bit) */

    TL0 = 0x00;
    TH0 = 0x00;
    TF0 = 0;

    while (1)
    {
        TR0 = 1;   /* Start counter */

        P1 = TL0;  /* Display lower 8 bits */
        P2 = TH0;  /* Display upper 8 bits */

        if (TF0 == 1)
        {
            TR0 = 0;  /* Stop after overflow */
            TF0 = 0;  /* Clear overflow flag */
        }
    }
}


2. Explanation
Register/bit	Purpose
T0 / P3.4	External pulse input
TMOD = 0x05	Selects Counter 0, Mode 1
TL0	Stores the lower 8 bits of the count
TH0	Stores the upper 8 bits of the count
TR0 = 1	Starts Counter 0
TF0	Set when the 16-bit counter overflows
P1 = TL0	Displays the low byte on Port 1
P2 = TH0	Displays the high byte on Port 2
Why is TMOD = 0x05?
TMOD = 0000 0101B
GATE
0


C/T
0


M1
0


M0
0


GATE
0


C/T
1


M1
0


M0
1



- C/T = 1: External counter mode.
- M1 M0 = 01: Mode 1, a 16-bit counter.

3. How the counter works
The combined count is:
\[
\text{Count}=(TH0\times256)+TL0
\]

For example, if TH0 = 02H and TL0 = 09H:
\[
\text{Count}=2\times256+9=521
\]

The counter increments once for each valid external pulse. It overflows after FFFFH and rolls over to 0000H, setting TF0.
Important: The program above stops the counter when overflow occurs. If your objective is to count continuously and display the live values, remove the if (TF0 == 1) block and leave the counter running. Also, for a 1 Hz input, the count advances only once per second, so the displayed values change slowly.