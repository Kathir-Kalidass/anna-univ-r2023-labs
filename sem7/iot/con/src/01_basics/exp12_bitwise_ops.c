/* Experiment 12 : Bitwise operations (AND, OR, XOR, NOT) */
#include "mcu51.h"

void main(void)
{
    unsigned char a = 0x0F;   /* 0000 1111 */
    unsigned char b = 0x33;   /* 0011 0011 */

    while(1)
    {
        P1 = a & b;   /* AND  = 0x03  (0000 0011) */
        P2 = a | b;   /* OR   = 0x3F  (0011 1111) */
        P3 = a ^ b;   /* XOR  = 0x3C  (0011 1100) */
        P0 = ~a;      /* NOT  = 0xF0  (1111 0000) */
    }
}
