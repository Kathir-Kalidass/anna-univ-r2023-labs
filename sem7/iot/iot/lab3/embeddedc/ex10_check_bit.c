/*
 * Activity 10: Check specific bit set or clear
 * Byte=0xA5, check bit 3 -> SET -> P1.0 ON
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char byte_val = 0xA5;  /* 10100101b */
    unsigned char bit_num = 3;      /* Bit to check */
    unsigned char mask;

    mask = 0x01 << bit_num;         /* Create mask for bit 3 = 0x08 */

    if (byte_val & mask) {
        P1 = 0x01;          /* Bit is SET: P1.0 ON */
    } else {
        P1 = 0x80;          /* Bit is CLEAR: P1.7 ON */
    }

    while (1);
}
