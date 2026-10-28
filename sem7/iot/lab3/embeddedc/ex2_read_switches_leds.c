/*
 * Activity 2: Read switches and display on LEDs
 * Switches on P0, LEDs on P1
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    P0 = 0xFF;     /* Configure P0 as input */

    while (1) {
        P1 = P0;   /* Mirror switches to LEDs */
    }
}
