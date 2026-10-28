/*
 * Activity 3: Bit-Addressable Registers
 * Access and modify specific bits in RAM and SFR locations
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

/* Bit-addressable RAM locations (20H-2FH) mapped to sbit */
sbit BIT_00 = 0x00;    /* 20H.0 */
sbit BIT_07 = 0x07;    /* 20H.7 */
sbit BIT_08 = 0x08;    /* 21H.0 */
sbit BIT_0F = 0x0F;    /* 21H.7 */
sbit BIT_10 = 0x10;    /* 22H.0 */

/* Port bits */
sbit P1_0 = P1^0;
sbit P1_3 = P1^3;
sbit P1_7 = P1^7;

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    /* Set bits in bit-addressable RAM */
    BIT_00 = 1;         /* 20H = 01H */
    BIT_07 = 1;         /* 20H = 81H */
    BIT_08 = 1;         /* 21H = 01H */
    BIT_0F = 1;         /* 21H = 81H */
    BIT_10 = 1;         /* 22H = 01H */

    /* Read bit values */
    if (BIT_00 == 1)    /* True */
        P1_0 = 1;

    /* Clear specific bits */
    BIT_07 = 0;         /* 20H = 01H */
    BIT_00 = 0;         /* 20H = 00H */

    /* Toggle a bit */
    BIT_08 = 0;         /* 01H -> 00H */
    BIT_08 = 1;         /* 00H -> 01H */

    /* Display byte values */
    P1 = 0x00;
    P1 |= (BIT_10 << 0);  /* Copy bit to P1.0 */
    P1 |= (BIT_08 << 1);

    /* Bit-addressable SFRs */
    P1_0 = 1;              /* SETB 90H */
    P1_3 = 1;              /* SETB 93H */
    delay();
    P1_0 = 0;              /* CLR 90H */

    /* Conditional bit test */
    if (P1_3 == 1) {       /* JB P1.3 */
        P1 = 0x0F;
    }

    /* JBC: Test and clear */
    if (P1_7 == 1) {       /* JBC P1.7 */
        P1_7 = 0;          /* Auto-clear after test */
    }

    while (1);
}
