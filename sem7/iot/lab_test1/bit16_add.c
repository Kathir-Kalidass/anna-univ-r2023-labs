8051 Embedded C: 16-bit Addition and Subtraction
Aim: To perform 16-bit addition and subtraction of two numbers using Embedded C in MCU 8051 IDE (SDCC).
Program
#include <8051.h>

unsigned int num1 = 0x1234;
unsigned int num2 = 0x0234;

unsigned int add_result;
unsigned int sub_result;

void main(void)
{
    add_result = num1 + num2;
    sub_result = num1 - num2;

    while (1);
}


Explanation
- unsigned int stores a 16-bit value in SDCC's 8051 C environment.
- num1 = 1234H and num2 = 0234H.
- add_result stores the addition result.
- sub_result stores the subtraction result.
- while (1) keeps the program running so you can inspect the variables.
Expected output
Operation	Calculation	Result (hex)	Result (decimal)
Addition	1234H + 0234H	1468H	5224
Subtraction	1234H − 0234H	1000H	4096
How to view the output
1. Compile and run the program.
2. Open the C Variables panel in MCU 8051 IDE.
3. Inspect add_result and sub_result.
4. If values are displayed in hexadecimal, expect 1468 and 1000.
Exam note: The 8051 is an 8-bit microcontroller, so 16-bit arithmetic is generally implemented using multiple byte-level operations. C handles this through the compiler.


To view the 16-bit addition and subtraction results directly in the 8051 registers, store the high byte and low byte of each result in separate registers or ports. The 8051 registers R0–R7 are only 8-bit, so each 16-bit result needs two 8-bit registers.
Program — SDCC-compatible for MCU 8051 IDE
#include <8051.h>

unsigned int num1 = 0x1234;
unsigned int num2 = 0x0234;

void main(void)
{
    unsigned int add_result;
    unsigned int sub_result;

    add_result = num1 + num2;
    sub_result = num1 - num2;

    /* Display addition result on P2:P1 */
    P2 = (unsigned char)(add_result >> 8);
    P1 = (unsigned char)add_result;

    while (1);
}


This displays the addition result in the SFR register panel:
- P2 = 14H — high byte
- P1 = 68H — low byte
The subtraction result is not displayed by this version. To inspect both results, use the following version, which alternates between addition and subtraction every second.
#include <8051.h>

unsigned int num1 = 0x1234;
unsigned int num2 = 0x0234;
unsigned int result;
unsigned int i, j;

void delay(void)
{
    for (i = 0; i < 100; i++)
        for (j = 0; j < 1200; j++)
            ;
}

void main(void)
{
    while (1)
    {
        result = num1 + num2;
        P2 = (unsigned char)(result >> 8);
        P1 = (unsigned char)result;
        delay();

        result = num1 - num2;
        P2 = (unsigned char)(result >> 8);
        P1 = (unsigned char)result;
        delay();
    }
}


Expected register values
Operation	P2 (high byte)	P1 (low byte)
Addition: 1234H + 0234H = 1468H	14H	68H
Subtraction: 1234H − 0234H = 1000H	10H	00H
How to view: Run the program and open the SFR/register panel. Observe P2 and P1; the values will alternate between the addition and subtraction results.