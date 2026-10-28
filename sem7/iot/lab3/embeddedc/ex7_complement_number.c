/*
 * Activity 7: Complement 8-bit number and display
 * Number complemented and shown on P1
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char number = 0x55;    /* 01010101b */
    unsigned char result;

    result = ~number;               /* Complement: A9H */
    P1 = result;

    while (1);
}
