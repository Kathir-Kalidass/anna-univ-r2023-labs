#include <8051.h>

void main(void)
{
    unsigned char num;

    num = ACC;

    if (num & 0x01)
        P1 = 0x80;    /* Odd: last LED ON */
    else
        P1 = 0x01;    /* Even: first LED ON */

    while (1);
}
/*Explanation
- num = ACC; — reads the 8-bit number from the accumulator.
- num & 0x01 — checks the least significant bit (LSB).
- If the LSB is 1, the number is odd; P1 = 0x80 turns ON the last LED, P1.7.
- If the LSB is 0, the number is even; P1 = 0x01 turns ON the first LED, P1.0.
- Assigning 0x80 or 0x01 to P1 ensures that only one bit is 1, so only one LED is ON at a time (assuming active-high LEDs).*/