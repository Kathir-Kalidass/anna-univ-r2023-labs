/*
 * Activity 5: Modifying PSW Register
 * PSW bits: CY AC F0 RS1 RS0 OV -- P
 * Demonstrates register bank switching and flag manipulation
 * MCUSim 8051 IDE - Embedded C (SDCC compatible)
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char psw_val;

    /* Default PSW */
    psw_val = PSW;
    P1 = psw_val;
    delay();

    /* Set CY (Carry Flag) */
    __asm
        SETB C
    __endasm;
    P1 = PSW;
    delay();

    /* Clear CY */
    __asm
        CLR C
    __endasm;
    P1 = PSW;
    delay();

    /* Set AC (Auxiliary Carry) - bit 6 */
    PSW = PSW | 0x40;
    P1 = PSW;
    delay();

    /* Set F0 (User Flag) - bit 5 */
    PSW = PSW | 0x20;
    P1 = PSW;
    delay();

    /* Switch to Register Bank 1: RS1=0, RS0=1 */
    PSW = (PSW & 0xE7) | 0x08;
    P1 = PSW;
    delay();

    /* Switch to Register Bank 2: RS1=1, RS0=0 */
    PSW = (PSW & 0xE7) | 0x10;
    P1 = PSW;
    delay();

    /* Switch to Register Bank 3: RS1=1, RS0=1 */
    PSW = PSW | 0x18;
    P1 = PSW;
    delay();

    /* Reset PSW */
    PSW = 0x00;
    P1 = PSW;

    while (1);
}
