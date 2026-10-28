#include <8051.h>

void main(void)
{
    unsigned char data, i, count;

    P1 = 0xFF;

    while (1)
    {
        data = P1;
        count = 0;

        for (i = 0; i < 8; i++)
        {
            if (data & 0x01)
                count++;

            data = data >> 1;
        }

        ACC = count;
        B = count;
    }
}

/*
Explanation
1. data = P1 reads the input byte.
2. count = 0 initializes the count.
3. The loop checks all 8 bits.
4. data & 0x01 checks whether the least significant bit is 1.
5. count++ increments the count when a 1 is found.
6. data >> 1 shifts the next bit into the least significant position.
7. ACC and B store the final count for verification.
Example
If P1 = 10110101B:
There are 5 ones in the input.
Register	Value
P1	B5H
ACC	05H
B	05H
Note: This program counts the set bits in software. The C/T bit of TMOD selects timer or external-event counter operation; it is not needed for this software bit-counting method.*/