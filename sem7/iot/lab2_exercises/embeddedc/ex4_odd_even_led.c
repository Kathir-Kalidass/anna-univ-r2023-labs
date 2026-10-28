/*
 * Exercise 4: Odd/Even Check with LED
 * Even -> LED P1.0 ON, Odd -> LED P1.7 ON
 * Only one LED ON at a time
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char number = 0x36;    /* Change to test: 0x36=even, 0x37=odd */
    unsigned char result;

    P1 = 0x00;                     /* Clear all LEDs */

    result = number & 0x01;        /* Check LSB */

    if (result == 0) {
        P1 = 0x01;                 /* Even: turn ON P1.0 only */
    } else {
        P1 = 0x80;                 /* Odd: turn ON P1.7 only */
    }

    while (1);
}
