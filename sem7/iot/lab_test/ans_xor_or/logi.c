#include <8051.h>

__data __at (0x30) unsigned char a;
__data __at (0x31) unsigned char b;
__data __at (0x32) unsigned char and_result;
__data __at (0x33) unsigned char or_result;
__data __at (0x34) unsigned char xor_result;

void main(void)
{
    a = 0x5A;
    b = 0x3C;

    ACC = a & b;
    and_result = ACC;

    ACC = a | b;
    or_result = ACC;

    ACC = a ^ b;
    xor_result = ACC;

    while (1);
}
/*Where to see the results
In MCU 8051 IDE:
1. Compile and run the program.
2. Open the Simulator or memory view.
3. Inspect internal RAM addresses 30H to 34H.
4. Check the accumulator (ACC) for the last result.
Internal RAM address	Stored value	Meaning
30H	5AH	First number
31H	3CH	Second number
32H	18H	AND result
33H	7EH	OR result
34H	66H	XOR result
ACC	66H	Final XOR result
Why this works: __data __at (...) places each variable at a fixed internal RAM address, and assigning a result to ACC makes it visible in the accumulator register.*/

/*Explanation
- a and b store the two 8-bit input numbers in external memory.
- & performs the AND operation.
- | performs the OR operation.
- ^ performs the XOR operation.
- The results are stored at separate memory locations for verification.
Expected output
Inputs: a = 5AH, b = 3CH
Operation	Result	Memory location
AND	18H	2002H
OR	7EH	2003H
XOR	66H	2004H
Memory map
Memory address	Content
2000H	First number (5AH)
2001H	Second number (3CH)
2002H	AND result (18H)
2003H	OR result (7EH)
2004H	XOR result (66H)
Note: This program uses SDCC-specific __xdata declarations and requires the simulator to support external data memory at these addresses.

#include <8051.h>

volatile unsigned char a = 0x5A, b = 0x3C;
volatile unsigned char and_result, or_result, xor_result;

void main(void)
{
    and_result = a & b;
    or_result  = a | b;
    xor_result = a ^ b;

    while (1);
}*/