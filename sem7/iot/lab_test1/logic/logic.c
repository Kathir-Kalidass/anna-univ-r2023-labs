#include <8051.h>

void main(void)
{
    unsigned char a, b;

    P1 = 0xFF;    /* Port 1 as input */
    P2 = 0xFF;    /* Port 2 as input */

    while (1)
    {
        a = P1;
        b = P2;

        ACC = a & b;    /* AND result */
        B = a | b;      /* OR result */
        P3 = a ^ b;     /* XOR result */
    }
}
