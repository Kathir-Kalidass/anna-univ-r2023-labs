/*
 * Activity 9: Even/Odd using logical operations
 * LSB=0 -> Even (P1.0), LSB=1 -> Odd (P1.7)
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char number = 0x37;    /* Test number */

    if ((number & 0x01) == 0) {
        P1 = 0x01;          /* Even: P1.0 ON */
    } else {
        P1 = 0x80;          /* Odd: P1.7 ON */
    }

    while (1);
}
