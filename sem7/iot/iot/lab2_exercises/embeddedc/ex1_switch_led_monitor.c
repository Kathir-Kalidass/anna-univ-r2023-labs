/*
 * Exercise 1: Continuously Monitor Switches & Update LEDs
 * Switches on P0 (input), LEDs on P1 (output)
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    P0 = 0xFF;     /* Configure P0 as input */

    while (1) {
        P1 = P0;   /* Mirror switch states directly to LEDs */
    }
}
