8051 Embedded C: Read and Display P0, P1, ACC, B, PSW, SP and DPTR
Aim: To read and display the values of important 8051 registers using Embedded C in MCU 8051 IDE.
Program — SDCC-compatible
#include <8051.h>

unsigned char value_P0;
unsigned char value_P1;
unsigned char value_ACC;
unsigned char value_B;
unsigned char value_PSW;
unsigned char value_SP;
unsigned int value_DPTR;

void main(void)
{
    /* Assign test values to registers */
    P0 = 0x55;
    P1 = 0xAA;
    ACC = 0x25;
    B = 0x05;
    PSW = 0x00;
    SP = 0x5F;
    DPTR = 0x1234;

    /* Read register values */
    value_P0 = P0;
    value_P1 = P1;
    value_ACC = ACC;
    value_B = B;
    value_PSW = PSW;
    value_SP = SP;
    value_DPTR = DPTR;

    while (1);
}


Expected output
Register	Expected value	Purpose
P0	55H	Port 0
P1	AAH	Port 1
ACC	25H	Accumulator
B	05H	Used in multiplication and division
PSW	00H	Program Status Word
SP	5FH	Stack Pointer
DPTR	1234H	16-bit Data Pointer
How to view the output in MCU 8051 IDE
1. Compile and run the program.
2. Open the SFR/Register panel.
3. Observe P0, P1, ACC, B, PSW, SP, DPH, and DPL.
4. Open the C Variables panel to inspect the copied values.
Note: DPTR is a 16-bit register made up of DPH (high byte) and DPL (low byte). For DPTR = 1234H, expect DPH = 12H and DPL = 34H.
On actual 8051 hardware, Port 0 requires external pull-up resistors when used as a general-purpose I/O port. The simulator may represent port values differently depending on its virtual hardware configuration.