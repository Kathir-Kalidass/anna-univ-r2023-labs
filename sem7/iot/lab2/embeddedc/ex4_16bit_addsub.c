/*
 * Exercise 4: 16-bit Addition and Subtraction of Two Numbers
 * Number1 = 0x1234, Number2 = 0x0F0F
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned int num1 = 0x1234;
    unsigned int num2 = 0x0F0F;
    unsigned int sum, diff;

    /* 16-bit Addition */
    sum = num1 + num2;          /* sum = 0x2143 */

    /* Send low byte to P1, high byte to P2 */
    P1 = (unsigned char)(sum & 0xFF);       /* P1 = 0x43 */
    P2 = (unsigned char)((sum >> 8) & 0xFF); /* P2 = 0x21 */

    /* 16-bit Subtraction */
    diff = num1 - num2;         /* diff = 0x0325 */

    /* Send low byte to P1, high byte to P2 */
    P1 = (unsigned char)(diff & 0xFF);       /* P1 = 0x25 */
    P2 = (unsigned char)((diff >> 8) & 0xFF); /* P2 = 0x03 */

    while (1);     /* Stop here */
}
