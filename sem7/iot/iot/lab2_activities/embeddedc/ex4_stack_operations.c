/*
 * Activity 4: Stack Operations - PUSH and POP
 * Demonstrates stack pointer behavior and data preservation
 * MCUSim 8051 IDE - Embedded C (SDCC compatible)
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 100; i++)
        for (j = 0; j < 200; j++) ;
}

/* Subroutine demonstrating stack save/restore */
unsigned char save_and_modify(unsigned char input) {
    unsigned char saved;
    saved = input;
    input = 0x99;
    P1 = input;
    delay();
    return saved;
}

void main(void) {
    unsigned char val;
    unsigned char sp_before;

    sp_before = SP;
    P2 = sp_before;

    /* Set SP to 2FH */
    __asm
        MOV SP, #2FH
    __endasm;

    /* Push values */
    __asm
        MOV A, #55H
        PUSH ACC
        MOV A, #0AAH
        PUSH ACC
    __endasm;

    P2 = SP;                    /* P2 = 31H */

    /* Pop values (LIFO order) */
    __asm
        POP ACC
    __endasm;
    P1 = ACC;                   /* P1 = AAH */
    delay();

    __asm
        POP ACC
    __endasm;
    P1 = ACC;                   /* P1 = 55H */
    delay();

    P2 = SP;                    /* P2 = 2FH */

    val = save_and_modify(0x42);
    P1 = val;                   /* P1 = 42H */

    while (1);
}
