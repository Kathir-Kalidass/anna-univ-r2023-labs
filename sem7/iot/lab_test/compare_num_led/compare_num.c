#include <8051.h>

void main(void)
{
    unsigned char a = 25, b = 15;

    if (a > b)
        P1 = 0x01;    /* First LED ON */
    else if (b > a)
        P1 = 0x02;    /* Second LED ON */
    else
        P1 = 0x04;    /* Third LED ON */

    while (1);
}

/*
Explanation
- a = 25, b = 15 — two 8-bit numbers.
- a > b — turns ON the first LED at P1.0.
- b > a — turns ON the second LED at P1.1.
- Otherwise, both numbers are equal, so the third LED at P1.2 turns ON.
- while (1); keeps the result displayed continuously.
Example outputs
First number (a)	Second number (b)	LED ON
25	15	P1.0
10	20	P1.1
15	15	P1.2
Note: This assumes active-high LEDs. Assigning 0x01, 0x02, or 0x04 to P1 ensures that only one LED is ON at a time.*/