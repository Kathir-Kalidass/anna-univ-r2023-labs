CS23E01 – Embedded Systems and IoT: 8051 ALU and Bit Operations Lab
These three experiments cover 8-bit ALU operations, 16-bit arithmetic operations, and bit-addressable RAM access. Since you're using the MCU 8051 IDE with SDCC, the programs below use #include <8051.h> and SDCC-compatible C syntax.
Experiment 1: Perform basic 8-bit ALU operations
Aim: To perform arithmetic, logical, rotate, complement, clear, and set operations on the 8051 simulator.
Program (Embedded C)
#include <8051.h>

unsigned char a = 25;
unsigned char b = 10;

unsigned char add_result;
unsigned char sub_result;
unsigned int mul_result;
unsigned char div_result;
unsigned char and_result;
unsigned char or_result;
unsigned char xor_result;
unsigned char rl_result;
unsigned char rr_result;
unsigned char cpl_result;
unsigned char clr_result;
unsigned char setb_result;

void main(void)
{
    add_result = a + b;       /* ADD */
    sub_result = a - b;       /* SUB */
    mul_result = a * b;       /* MUL */
    div_result = a / b;       /* DIV */

    and_result = a & b;       /* ANL */
    or_result  = a | b;       /* ORL */
    xor_result = a ^ b;       /* XRL */

    ACC = 0x81;
    RL A;
    rl_result = ACC;

    ACC = 0x81;
    RR A;
    rr_result = ACC;

    ACC = 0x55;
    CPL A;
    cpl_result = ACC;

    ACC = 0xFF;
    CLR A;
    clr_result = ACC;

    ACC = 0x00;
    SETB C;
    setb_result = C;

    while (1);
}


Important SDCC note: RL A, RR A, CPL A, CLR A, and SETB C are 8051 assembly instructions, not ordinary C statements. The lines above illustrate the intended operations, but they will not compile as standard SDCC C. Use the following corrected, compilable C version for the simulator.
Corrected 8-bit program — SDCC-compatible
This version compiles as Embedded C and demonstrates the equivalent results. It does not guarantee that the compiler generates each named 8051 instruction.
#include <8051.h>

unsigned char a = 25;
unsigned char b = 10;

unsigned char add_result, sub_result;
unsigned int mul_result;
unsigned char div_result;
unsigned char and_result, or_result, xor_result;
unsigned char rl_result, rr_result;
unsigned char cpl_result, clr_result, setb_result;

void main(void)
{
    add_result = a + b;
    sub_result = a - b;
    mul_result = (unsigned int)a * b;
    div_result = a / b;

    and_result = a & b;
    or_result  = a | b;
    xor_result = a ^ b;

    /* Rotate left and right */
    a = 0x81;
    rl_result = (a << 1) | (a >> 7);

    a = 0x81;
    rr_result = (a >> 1) | (a << 7);

    /* Complement, clear and set */
    cpl_result = (unsigned char)~0x55;
    clr_result = 0x00;
    setb_result = 0x01;

    while (1);
}


Expected results
Operation	Calculation	Result
ADD	25 + 10	35 (23H)
SUB	25 − 10	15 (0FH)
MUL	25 × 10	250 (00FAH)
DIV	25 ÷ 10	2; remainder 5
ANL	19H & 0AH	08H
ORL	19H \| 0AH	1BH
XRL	19H ^ 0AH	13H
RL	Rotate 81H left	03H
RR	Rotate 81H right	C0H
CPL	Complement 55H	AAH
CLR	Clear accumulator equivalent	00H
SETB	Set a bit to 1	01H
Exam point: RL A and RR A rotate the accumulator bits without using the carry flag. RLC A and RRC A rotate through carry instead.
For the actual instruction-level experiment, use 8051 Assembly or SDCC inline assembly if your instructor requires the exact mnemonics.

Experiment 2: Perform 16-bit ALU operations
Aim: To perform 16-bit arithmetic and logical operations and compare their results with 8-bit operations.
Program (Embedded C)
#include <8051.h>

unsigned int a16 = 500;
unsigned int b16 = 20;

unsigned int add16, sub16;
unsigned long mul16;
unsigned int div16;
unsigned int and16, or16, xor16;
unsigned int rl16, rr16, cpl16;

void main(void)
{
    add16 = a16 + b16;
    sub16 = a16 - b16;
    mul16 = (unsigned long)a16 * b16;
    div16 = a16 / b16;

    and16 = a16 & b16;
    or16  = a16 | b16;
    xor16 = a16 ^ b16;

    /* 16-bit rotate equivalents */
    rl16 = (unsigned int)((a16 << 1) | (a16 >> 15));
    rr16 = (unsigned int)((a16 >> 1) | (a16 << 15));

    cpl16 = (unsigned int)~a16;

    while (1);
}


Expected results
Operation	Calculation	Result
ADD	500 + 20	520 (0208H)
SUB	500 − 20	480 (01E0H)
MUL	500 × 20	10,000 (2710H)
DIV	500 ÷ 20	25 (0019H)
The remaining logical and rotate results can be inspected in the simulator's C Variables window.
Difference between 8-bit and 16-bit operations
Feature	8-bit	16-bit
Data width	8 bits	16 bits
Unsigned range	0–255	0–65,535
Storage	1 byte	2 bytes
Addition	May overflow beyond 255	May overflow beyond 65,535
Multiplication	8-bit operands can produce 16-bit results	16-bit operands can produce up to 32-bit results
Execution	Often fewer instructions	Usually requires more instructions on an 8051
Important: The original 8051 is an 8-bit microcontroller. Its native MUL AB multiplies two 8-bit values and produces a 16-bit result in B:ACC. DIV AB divides the 8-bit accumulator by the 8-bit B register, placing the quotient in ACC and remainder in B. General 16-bit C operations are typically implemented using multiple machine instructions.

Experiment 3: Access and change a specific bit in bit-addressable RAM
Aim: To set, clear, and read an individual bit in the 8051's bit-addressable internal RAM using Embedded C.
Concept
Bit-addressable RAM region
Internal RAM: 20H–2FH
16 bytes × 8 bits = 128 individually addressable bits

Example byte: 20H

b7
0


b6
0


b5
0


b4
0


b3
0


b2
0


b1
0


b0
1



Example: bit address 00H refers to bit 0 of RAM byte 20H.

Program (SDCC-compatible C)
#include <8051.h>

/* Bit address 00H = bit 0 of internal RAM byte 20H */
__sbit __at (0x00) RAM_20H_BIT0;

unsigned char read_result;

void main(void)
{
    RAM_20H_BIT0 = 0;       /* Clear the bit */
    RAM_20H_BIT0 = 1;       /* Set the bit */

    read_result = RAM_20H_BIT0;  /* Read the bit */

    RAM_20H_BIT0 = !RAM_20H_BIT0; /* Toggle the bit */

    while (1);
}


Procedure
1. Create a C project in MCU 8051 IDE and select SDCC.
2. Compile and load the program.
3. Run or single-step through the statements.
4. Inspect internal RAM location 20H and verify bit 0 changes.
5. Confirm that read_result stores the value read before the toggle.
Expected observation
Statement	Bit 0 of RAM location 20H
RAM_20H_BIT0 = 0;	0
RAM_20H_BIT0 = 1;	1
read_result = RAM_20H_BIT0;	Reads 1
RAM_20H_BIT0 = !RAM_20H_BIT0;	0
Remember: The 8051 has two important bit-addressable areas: internal RAM bytes 20H–2FH and certain bit-addressable SFRs. Not every RAM location or SFR is individually bit-addressable.
One distinction for your record: the C programs demonstrate the operations and results. If your practical evaluator explicitly requires the actual ADD, SUBB, MUL AB, DIV AB, ANL, ORL, XRL, RL, RR, CPL, CLR, and SETB machine instructions, use an assembly-language program for Experiment 1, because equivalent C expressions may compile to different instructions.