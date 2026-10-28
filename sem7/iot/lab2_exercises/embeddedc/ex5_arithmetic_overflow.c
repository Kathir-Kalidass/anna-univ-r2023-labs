/*
 * Exercise 5: 8-bit Arithmetic with Overflow/Carry LEDs
 * P1.7=Carry, P1.6=Borrow, P1.5=MUL overflow, P1.4=DIV by zero
 * Results stored in different register banks
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char a = 200;
    unsigned char b = 100;
    unsigned int  result;
    unsigned char quotient, remainder;

    P1 = 0x00;     /* Clear all LEDs */

    /* ADDITION */
    result = (unsigned int)a + (unsigned int)b;
    if (result > 0xFF)
        P1 |= 0x80;            /* Carry LED P1.7 ON */

    /* SUBTRACTION */
    if (a < b)
        P1 |= 0x40;            /* Borrow LED P1.6 ON */

    /* MULTIPLICATION */
    result = (unsigned int)a * (unsigned int)b;
    if (result > 0xFF)
        P1 |= 0x20;            /* MUL overflow LED P1.5 ON */

    /* DIVISION */
    if (b != 0) {
        quotient  = a / b;
        remainder = a % b;
    } else {
        P1 |= 0x10;            /* Division by zero LED P1.4 ON */
    }

    while (1);
}
