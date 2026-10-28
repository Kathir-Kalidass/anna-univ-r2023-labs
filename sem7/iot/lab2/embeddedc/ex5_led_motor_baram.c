/*
 * Exercise 5: Control LED and Motor using Bit-Addressable RAM
 * LED on P1.0, Motor on P1.7
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

/* Sbit definitions for direct bit control */
sbit LED   = P1^0;     /* LED connected to P1.0 */
sbit MOTOR = P1^7;     /* Motor connected to P1.7 */

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++)
            ;
}

void main(void) {

    /* Toggle LED */
    LED = 1;            /* LED ON */
    delay();
    LED = 0;            /* LED OFF */

    /* Toggle Motor */
    MOTOR = 1;          /* Motor ON */
    delay();
    MOTOR = 0;          /* Motor OFF */

    /* Pattern display on P1 */
    P1 = 0x0F;          /* Lower nibble ON */
    delay();
    P1 = 0xF0;          /* Upper nibble ON */
    delay();
    P1 = 0x55;          /* Alternating pattern */
    delay();
    P1 = 0x00;          /* All OFF */

    while (1);
}
