/*
 * Exercise 2: Count Number of 1s in an 8-bit Number
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char number = 0xA5;  /* 10100101b -> should count 5 ones */
    unsigned char count = 0;
    unsigned char i;

    for (i = 0; i < 8; i++) {
        if (number & 0x01)       /* Check LSB */
            count++;
        number >>= 1;            /* Shift right to check next bit */
    }

    P1 = count;     /* Display count of 1s on Port 1 */

    while (1);      /* Stop here */
}
