/* Experiment 6 : Running LED - Right shift (10000000 -> 00000001) */
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    unsigned char x = 0x80;   /* start at bit7 */

    while(1)
    {
        P1 = x;
        delay();
        x = x >> 1;           /* shift right */

        if(x == 0)            /* wrap back to bit7 */
            x = 0x80;
    }
}
