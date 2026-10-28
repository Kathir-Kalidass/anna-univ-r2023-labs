/*
 * Activity 5: Circular LED pattern using rotate instructions
 * Single bit circles P1.0->P1.7 then back P1.7->P1.0
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 150; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char led = 0x01;
    unsigned char direction = 0;  /* 0=left, 1=right */

    while (1) {
        P1 = led;
        delay();

        if (direction == 0) {
            led = (led << 1) | (led >> 7);  /* Rotate left */
            if (led == 0x80)           /* Reached P1.7 */
                direction = 1;         /* Switch to right */
        } else {
            led = (led >> 1) | (led << 7);  /* Rotate right */
            if (led == 0x01)           /* Reached P1.0 */
                direction = 0;         /* Switch to left */
        }
    }
}
