#include <8051.h>

__sfr __at (0xD0) PSW_REG;
__sfr __at (0x90) P1_REG;
__sfr __at (0xA0) P2_REG;
__sfr __at (0xB0) P3_REG;

__data __at (0x00) B0_R0;
__data __at (0x08) B1_R0;
__data __at (0x10) B2_R0;
__data __at (0x11) B2_R1;
__data __at (0x18) B3_R0;

void main(void)
{
    unsigned char a = 20, b = 10;
    unsigned int result;

    /* Bank 0: Addition */
    PSW_REG = 0x00;
    result = a + b;
    B0_R0 = result & 0xFF;
    P1_REG = (result > 255) ? 0x80 : 0x00;

    /* Bank 1: Subtraction */
    PSW_REG = 0x08;
    B1_R0 = a - b;
    P2_REG = (a < b) ? 0x80 : 0x00;

    /* Bank 2: Multiplication */
    PSW_REG = 0x10;
    result = a * b;
    B2_R0 = result & 0xFF;
    B2_R1 = (result >> 8) & 0xFF;
    P3_REG = (result > 255) ? 0x80 : 0x00;

    /* Bank 3: Division */
    PSW_REG = 0x18;
    if (b != 0)
        B3_R0 = a / b;
    else
        B3_R0 = 0;

    while (1);
}


/*
Explanation
Operation	Register bank	Result storage	LED indication
Addition	Bank 0	R0	P1.7 ON if result exceeds 255
Subtraction	Bank 1	R0	P2.7 ON if borrow occurs
Multiplication	Bank 2	R0 (low byte), R1 (high byte)	P3.7 ON if result exceeds 255
Division	Bank 3	R0 (quotient)	No LED used
- PSW = 0x00 selects Bank 0.
- PSW = 0x08 selects Bank 1.
- PSW = 0x10 selects Bank 2.
- PSW = 0x18 selects Bank 3.
- result > 255 detects a result that does not fit in 8 bits.
- a < b detects unsigned subtraction underflow (borrow).
- Division by zero is avoided.
Important: Each register bank has its own R0–R7 registers. The code uses R0 in each bank to store that operation's result. The port LEDs indicate the conditions after each operation; because all operations run sequentially, the final LED states remain visible.
Example output
For \(a=20\) and \(b=10\):
Operation	Result
Addition	30
Subtraction	10
Multiplication	200
Division	2
No carry, borrow, or multiplication overflow LED is turned on for these inputs.



#include <8051.h>

void main(void)
{
    unsigned char a = 20, b = 10;
    unsigned int result;

    
    PSW = 0x00;
    result = a + b;
    R0 = result & 0xFF;
    P1 = (result > 255) ? 0x80 : 0x00;

    /* Register Bank 1: Subtraction 
    PSW = 0x08;
    R0 = a - b;
    P2 = (a < b) ? 0x80 : 0x00;

    /* Register Bank 2: Multiplication 
    PSW = 0x10;
    result = a * b;
    R0 = result & 0xFF;
    R1 = (result >> 8) & 0xFF;
    P3 = (result > 255) ? 0x80 : 0x00;

    /* Register Bank 3: Division 
    PSW = 0x18;
    if (b != 0)
        R0 = a / b;
    else
        R0 = 0;

    while (1);
}*/