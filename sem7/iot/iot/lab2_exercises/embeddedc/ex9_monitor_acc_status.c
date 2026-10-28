/*
 * Exercise 9: Monitor Accumulator Status with LEDs
 * ACC==0: LED P1.0 ON, ACC!=0: LED P1.1 ON
 * ACC.7==1: LED P1.2 ON then clear bit 7
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char acc_val;

    ACC = 0xFF;             /* Load test value: 0xFF, 0x00, 0x55, 0x80 */
    acc_val = ACC;

    P1 = 0x00;             /* Clear all LEDs */

    if (acc_val == 0) {
        P1 |= 0x01;         /* Zero: LED P1.0 ON */
    } else {
        P1 |= 0x02;         /* Non-zero: LED P1.1 ON */
    }

    if (acc_val & 0x80) {
        P1 |= 0x04;         /* Bit 7 set: LED P1.2 ON */
        ACC = ACC & 0x7F;   /* Clear bit 7 */
    }

    while (1);
}
