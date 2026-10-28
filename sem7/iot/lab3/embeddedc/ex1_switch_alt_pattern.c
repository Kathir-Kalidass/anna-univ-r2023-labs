/*
 * Activity 1: Switch flips alternately display AAH and 55H
 * Switch on P0.0, LEDs on P1
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

sbit SWITCH = P0^0;

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char pattern = 0x55;

    P1 = pattern;

    while (1) {
        if (SWITCH == 0) {          /* Switch pressed (active low) */
            delay();                /* Debounce */
            if (SWITCH == 0) {
                pattern = ~pattern;  /* Toggle AAH <-> 55H */
                P1 = pattern;
                while (SWITCH == 0); /* Wait release */
            }
        }
    }
}
