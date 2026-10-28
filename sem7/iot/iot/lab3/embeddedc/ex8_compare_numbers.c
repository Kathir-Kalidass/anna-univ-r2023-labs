/*
 * Activity 8: Compare two 8-bit numbers, 3 LEDs
 * P1.0: Num1>Num2, P1.1: Num2>Num1, P1.2: Equal
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char num1 = 30;
    unsigned char num2 = 30;

    P1 = 0x00;

    if (num1 > num2) {
        P1 = 0x01;          /* LED1: Num1 > Num2 */
    } else if (num2 > num1) {
        P1 = 0x02;          /* LED2: Num2 > Num1 */
    } else {
        P1 = 0x04;          /* LED3: Equal */
    }

    while (1);
}
