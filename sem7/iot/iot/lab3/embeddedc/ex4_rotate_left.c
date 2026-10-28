/*
 * Activity 4: Rotate 8-bit data left continuously
 * Data rotates left and displayed on P1
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char data_val = 0x01;

    while (1) {
        P1 = data_val;             /* Display on LEDs */
        delay();
        data_val = (data_val << 1) | (data_val >> 7);  /* Rotate left 1 bit */
    }
}
