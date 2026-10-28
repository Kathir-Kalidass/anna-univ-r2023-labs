/*
 * Activity 1: 8-bit Basic ALU Operations
 * Demonstrates: ADD, SUB, MUL, DIV, ANL, ORL, XRL, RL, RR, CPL, CLR, SETB
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char result;

    /* ADD: 25H + 1AH = 3FH */
    result = 0x25 + 0x1A;
    P1 = result;            /* P1 = 3FH */
    delay();

    /* SUB: 50H - 30H = 20H */
    result = 0x50 - 0x30;
    P1 = result;            /* P1 = 20H */
    delay();

    /* MUL: 05H * 06H = 1EH (low byte) */
    result = 0x05 * 0x06;
    P1 = result;            /* P1 = 1EH */
    delay();

    /* DIV: 25H / 06H = 06H */
    result = 0x25 / 0x06;
    P1 = result;            /* P1 = 06H */
    delay();

    /* ANL: C5H AND 6DH = 45H */
    result = 0xC5 & 0x6D;
    P1 = result;            /* P1 = 45H */
    delay();

    /* ORL: C5H OR 6DH = EDH */
    result = 0xC5 | 0x6D;
    P1 = result;            /* P1 = EDH */
    delay();

    /* XRL: C5H XOR 6DH = A8H */
    result = 0xC5 ^ 0x6D;
    P1 = result;            /* P1 = A8H */
    delay();

    /* RL: Rotate left by shifting */
    result = 0x01;
    result = (result << 3) | (result >> 5); /* Rotate left by 3: 01H -> 08H */
    P1 = result;            /* P1 = 08H */
    delay();

    /* RR: Rotate right by shifting */
    result = 0x80;
    result = (result >> 3) | (result << 5); /* Rotate right by 3: 80H -> 10H */
    P1 = result;            /* P1 = 10H */
    delay();

    /* CPL: Complement */
    result = 0x55;
    result = ~result;       /* CPL: 55H -> A9H */
    P1 = result;            /* P1 = A9H */
    delay();

    /* CLR: Clear */
    result = 0xFF;
    result = 0x00;          /* CLR A */
    P1 = result;            /* P1 = 00H */
    delay();

    /* SETB: Set bit */
    P1 = 0x00;
    P1 |= 0x01;             /* SETB P1.0 */
    P1 |= 0x80;             /* SETB P1.7 */
    /* P1 = 81H */

    while (1);
}
