/*
 * Activity 2: 16-bit ALU Operations
 * Demonstrates ADD, SUB, ANL, ORL, XRL on 16-bit numbers
 * Shows the need for carry/borrow chaining in 8051
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned int num1, num2, result;

    /* 16-bit Addition: 1234H + 0F0FH = 2143H */
    num1 = 0x1234;
    num2 = 0x0F0F;
    result = num1 + num2;       /* result = 0x2143 */
    P1 = (unsigned char)(result & 0xFF);     /* P1 = 43H (low) */
    P2 = (unsigned char)((result >> 8) & 0xFF); /* P2 = 21H (high) */
    delay();

    /* 16-bit Subtraction: 5678H - 1234H = 4444H */
    num1 = 0x5678;
    num2 = 0x1234;
    result = num1 - num2;       /* result = 0x4444 */
    P1 = (unsigned char)(result & 0xFF);
    P2 = (unsigned char)((result >> 8) & 0xFF);
    delay();

    /* 16-bit AND: C5A3H AND 6D5FH = 4503H */
    num1 = 0xC5A3;
    num2 = 0x6D5F;
    result = num1 & num2;       /* result = 0x4503 */
    P1 = (unsigned char)(result & 0xFF);
    P2 = (unsigned char)((result >> 8) & 0xFF);
    delay();

    /* 16-bit OR: C5A3H OR 6D5FH = EDFFH */
    num1 = 0xC5A3;
    num2 = 0x6D5F;
    result = num1 | num2;       /* result = 0xEDFF */
    P1 = (unsigned char)(result & 0xFF);
    P2 = (unsigned char)((result >> 8) & 0xFF);
    delay();

    /* 16-bit XOR: C5A3H XOR 6D5FH = A8FCH */
    num1 = 0xC5A3;
    num2 = 0x6D5F;
    result = num1 ^ num2;       /* result = 0xA8FC */
    P1 = (unsigned char)(result & 0xFF);
    P2 = (unsigned char)((result >> 8) & 0xFF);

    while (1);
}
