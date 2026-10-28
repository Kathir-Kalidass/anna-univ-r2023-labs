/*
 * Exercise 3: Running LED Pattern
 * LED moves from P1.0 to P1.7 then restarts
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 100; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char led = 0x01;   /* Start at P1.0 */

    while (1) {
        P1 = led;               /* Display current LED */
        delay();                /* Visible delay */
        led = led << 1;         /* Shift left: move to next position */

        if (led == 0x00)        /* If shifted past P1.7 */
            led = 0x01;         /* Restart from P1.0 */
    }
}
