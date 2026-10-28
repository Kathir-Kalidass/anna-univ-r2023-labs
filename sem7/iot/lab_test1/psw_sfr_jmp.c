8051 Embedded C Programs — Separate Programs (SDCC)
These programs are compatible with your Windows MCU 8051 IDE using SDCC. Each program is separate; compile and run them individually.
5. Modify the PSW Register
Aim: To modify the Program Status Word (PSW) register and select different register banks.
#include <8051.h>

void main(void)
{
    PSW = 0x00;   /* Select Register Bank 0 */
    R0 = 0x11;

    PSW = 0x08;   /* Select Register Bank 1 */
    R0 = 0x22;

    PSW = 0x10;   /* Select Register Bank 2 */
    R0 = 0x33;

    PSW = 0x18;   /* Select Register Bank 3 */
    R0 = 0x44;

    while (1);
}


Expected result: The four register banks contain different values in their respective R0 locations.
PSW value	Selected bank	R0 value
00H	0	11H
08H	1	22H
10H	2	33H
18H	3	44H
Note: The RS1 and RS0 bits of PSW select the register bank.

6. Access SFRs and Observe Their Values
Aim: Write values to selected Special Function Registers (SFRs) and inspect them in the MCU 8051 IDE SFR/register panel.
#include <8051.h>

void main(void)
{
    P0 = 0x55;
    P1 = 0xAA;
    P2 = 0x0F;
    P3 = 0xF0;

    ACC = 0x25;
    B = 0x05;
    PSW = 0x00;

    TMOD = 0x01;
    TH0 = 0x12;
    TL0 = 0x34;

    while (1);
}


How to verify: Compile and run the program, then inspect the SFR panel.
SFR	Address	Expected value
P0	80H	55H
SP	81H	Depends on startup
DPL	82H	Depends on startup
DPH	83H	Depends on startup
P1	90H	AAH
P2	A0H	0FH
P3	B0H	F0H
PSW	D0H	00H
ACC	E0H	25H
B	F0H	05H
Important: The 8051 SFR address range is 80H–FFH, but not every address represents a defined SFR. Some addresses are reserved or device-specific. This program demonstrates selected SFRs, not every address in the range.

7. Looping, Jumps, Subroutine Calls and Returns
Program 7(a): Loop using a register
Aim: Use a loop to increment a value ten times.
#include <8051.h>

void main(void)
{
    unsigned char i;
    unsigned char count = 0;

    for (i = 0; i < 10; i++)
    {
        count++;
    }

    ACC = count;

    while (1);
}


Expected result: ACC = 0AH.

Program 7(b): Conditional jump — zero or non-zero
Aim: Check whether the accumulator contains zero and display the result through Port 1.
#include <8051.h>

void main(void)
{
    ACC = 0x00;

    if (ACC == 0)
        P1 = 0x01;
    else
        P1 = 0x02;

    while (1);
}


Expected result: P1.0 is HIGH because the accumulator contains zero.
Equivalent 8051 assembly concepts:
- JZ — jump if accumulator is zero.
- JNZ — jump if accumulator is non-zero.

Program 7(c): Carry-based conditional jump
Aim: Demonstrate a carry condition during addition.
#include <8051.h>

void main(void)
{
    unsigned char a = 200;
    unsigned char b = 100;
    unsigned int result;

    result = a + b;

    if (result > 255)
        P1 = 0x80;
    else
        P1 = 0x00;

    while (1);
}


Expected result: P1.7 is HIGH because 200 + 100 = 300, which exceeds the 8-bit range.
This demonstrates the carry condition logically; it does not directly execute the assembly instruction JC.

Program 7(d): Compare two values
Aim: Compare two numbers and indicate which is greater.
#include <8051.h>

void main(void)
{
    unsigned char a = 25;
    unsigned char b = 15;

    if (a > b)
        P1 = 0x01;
    else if (a < b)
        P1 = 0x02;
    else
        P1 = 0x04;

    while (1);
}


Expected result: P1.0 is HIGH because a > b.
This demonstrates comparison in C; it does not directly execute the assembly instruction CJNE.

Program 7(e): Subroutine call and return
Aim: Call a function, increment a value, and return to the main program.
#include <8051.h>

unsigned char value = 5;

void increment(void)
{
    value++;
}

void main(void)
{
    increment();
    ACC = value;

    while (1);
}


Expected result: value = 6, and ACC = 06H.
The C function call and return demonstrate the concept of subroutines. The compiler determines the actual assembly instructions used.

Program 7(f): Infinite loop
Aim: Continuously toggle an LED on P1.0.
#include <8051.h>

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 30000; i++);
}

void main(void)
{
    while (1)
    {
        P1 = P1 ^ 0x01;
        delay();
    }
}


Expected result: The LED connected to P1.0 blinks continuously.

Important assembly instruction reference
Your syllabus lists specific 8051 assembly instructions. The C programs above demonstrate their concepts, but they do not guarantee that the compiler generates each named instruction.
Instruction	Purpose
AJMP	Absolute jump within a 2 KB code page
SJMP	Short relative jump
LJMP	Long jump anywhere in code memory
DJNZ	Decrement and jump if not zero
JC / JNC	Jump if carry set / clear
JZ / JNZ	Jump if accumulator zero / non-zero
JB / JNB	Jump if bit set / clear
JBC	Jump if bit set, then clear it
CJNE	Compare and jump if not equal
JMP	Unconditional indirect jump
ACALL / LCALL	Call a subroutine
RET	Return from subroutine
RETI	Return from interrupt service routine
For practical questions that explicitly require AJMP, DJNZ, CJNE, PUSH, POP, or other named assembly instructions, use assembly code or SDCC inline assembly rather than assuming ordinary C code will generate the requested instruction.