#include <8051.h>

void main(void)
{
    unsigned char a, b;
    unsigned int sum;

    P1 = 0xFF;       /* Port 1 as input */
    P2 = 0xFF;       /* Port 2 as input */

    while (1)
    {
        a = P1;      /* Read first byte */
        b = P2;      /* Read second byte */

        sum = a + b; /* Add the two bytes */

        ACC = sum & 0xFF;  /* Store lower 8 bits */
        B = (sum >> 8);    /* Store carry/high byte */
    }
}
/*Explanation
- a = P1 reads the first byte from Port 1.
- b = P2 reads the second byte from Port 2.
- sum = a + b adds both numbers.
- ACC stores the lower 8 bits of the sum.
- B stores the high byte, which is 01H if the sum exceeds 255, otherwise 00H.
Example
Suppose:
- P1 = 25H (37 decimal)
- P2 = 15H (21 decimal)
Then:
\[
25H + 15H = 3AH
\]

SFR / variable	Expected value
P1	25H
P2	15H
ACC	3AH
B	00H
If the sum exceeds FFH, ACC holds the lower byte and B holds the high byte.
In MCU 8051 IDE: Inspect the SFR/register view for P1, P2, ACC, and B. Since the loop runs continuously, the values update whenever the port inputs change.*/