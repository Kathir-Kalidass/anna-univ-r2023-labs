/*
 * Activity 3: Read 8-bit input, display complement
 * Input on P0, complemented output on P1
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    P0 = 0xFF;     /* P0 as input */

    while (1) {
        P1 = ~P0;  /* Read input, complement, display */
    }
}
