8051 Embedded C: Count the Number of 1's in an 8-bit Number
Aim: To count the number of set bits (1s) in an 8-bit binary number using Embedded C.
Program (SDCC-compatible)
#include <8051.h>

unsigned char num = 0xB5;
unsigned char count = 0;
unsigned char i;

void main(void)
{
    for (i = 0; i < 8; i++)
    {
        if (num & 0x01)
        {
            count++;
        }

        num = num >> 1;
    }

    while (1);
}


Explanation
Assume the input number is B5H.
Binary representation:
\[
\text{B5H}=10110101_2
\]

There are five 1s in this number.
The program checks the least significant bit using num & 0x01. If it is 1, the counter increments. Then the number shifts right by one bit, repeating eight times.
Dry run
Iteration	Bit checked	Count
1	1	1
2	0	1
3	1	2
4	0	2
5	1	3
6	1	4
7	0	4
8	1	5
Final output: count = 5
How to view the output in MCU 8051 IDE
1. Compile and run the program.
2. Open the C Variables panel.
3. Inspect count; it should be 5.
1. Inspect num; it will be 0 after all eight shifts.
Exam tip: The algorithm is: check LSB → increment if set → shift right → repeat eight times.