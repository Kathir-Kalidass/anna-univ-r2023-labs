/*
 * Exercise 3: Countdown from 10 to 0 with 1-second delay
 * MCUSim 8051 IDE - Embedded C
 * Crystal: 11.0592 MHz
 */
#include <8051.h>

/* ~1 second delay at 11.0592 MHz */
void delay_1sec(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 2500; j++)
            ;   /* Empty loop for delay */
}

void main(void) {
    unsigned char count;

    for (count = 10; count > 0; count--) {
        P1 = count;         /* Display current count on Port 1 */
        delay_1sec();       /* Wait ~1 second */
    }

    P1 = 0x00;             /* Display 0 */

    while (1);             /* Stop here */
}
