/*
 * Exercise 8: Exchange Two Registers, then INC/DEC
 * Exchange R0 and R1, then increment R0, decrement R1
 * Final values on P1 (R0) and P2 (R1)
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char r0 = 25;
    unsigned char r1 = 10;
    unsigned char temp;

    /* Exchange */
    temp = r0;
    r0 = r1;
    r1 = temp;

    /* After exchange: r0=10, r1=25 */

    r0++;       /* Increment R0 -> r0 = 11 */
    r1--;       /* Decrement R1 -> r1 = 24 */

    P1 = r0;    /* Display R0 on P1 (should show 0x0B) */
    P2 = r1;    /* Display R1 on P2 (should show 0x18) */

    while (1);
}
