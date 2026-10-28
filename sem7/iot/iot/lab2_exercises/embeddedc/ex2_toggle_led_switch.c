/*
 * Exercise 2: Toggle LED Using Switch
 * Switch on P0.0, LED on P1.0
 * Each switch press toggles the LED
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

sbit SWITCH = P0^0;
sbit LED    = P1^0;

void delay(void) {
    unsigned int i;
    for (i = 0; i < 5000; i++) ;
}

void main(void) {
    LED = 0;            /* LED initially OFF */

    while (1) {
        if (SWITCH == 0) {          /* Switch pressed (active low) */
            delay();                /* Debounce delay */
            if (SWITCH == 0) {      /* Confirm still pressed */
                LED = !LED;         /* Toggle LED */
                while (SWITCH == 0); /* Wait for release */
            }
        }
    }
}
