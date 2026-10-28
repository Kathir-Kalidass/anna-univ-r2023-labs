#include <8051.h>

void main(void)
{
    ACC = 0x80;

    while (1)
    {
        if (ACC == 0)
            P1 = 0x01;       /* First LED ON */
        else
            P1 = 0x02;       /* Second LED ON */

        if (ACC & 0x80)
        {
            ACC = ACC & 0x7F; /* Clear bit 7 */
            P1 = 0x04;        /* Third LED ON */
        }
    }
}

/*Explanation
- ACC = 0x80; initializes the accumulator to 10000000 in binary for demonstration.
- ACC == 0 checks whether the accumulator is zero.
- P1 = 0x01 turns ON the first LED if the accumulator is zero.
- P1 = 0x02 turns ON the second LED if it is non-zero.
- ACC & 0x80 checks whether bit 7 is set.
- ACC & 0x7F clears bit 7 while preserving the other bits.
- P1 = 0x04 turns ON the third LED when bit 7 was set.
LED mapping (active-high):
LED	Port pin	Condition
First	P1.0	Accumulator is zero
Second	P1.1	Accumulator is non-zero
Third	P1.2	Bit 7 was set and cleared
Note: The third LED assignment overrides the first or second LED assignment when bit 7 is set. Also, the accumulator is modified by clearing bit 7, so on the next loop iteration it may indicate a different status.*/