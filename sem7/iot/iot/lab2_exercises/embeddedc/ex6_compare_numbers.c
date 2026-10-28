/*
 * Exercise 6: Compare Two 8-bit Numbers
 * Num1 > Num2: LED P1.0 ON
 * Num2 > Num1: LED P1.1 ON
 * Equal: LED P1.2 ON
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char num1 = 45;
    unsigned char num2 = 45;     /* Change to test */

    P1 = 0x00;     /* Clear all LEDs */

    if (num1 > num2) {
        P1 = 0x01;              /* LED P1.0 ON: Num1 > Num2 */
    } else if (num2 > num1) {
        P1 = 0x02;              /* LED P1.1 ON: Num2 > Num1 */
    } else {
        P1 = 0x04;              /* LED P1.2 ON: Equal */
    }

    while (1);
}
