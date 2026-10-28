/* Experiment 5 : Running LED - Left shift (00000001 -> 10000000) */
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    unsigned char x = 0x01;   /* start at bit0 */

    while(1)
    {
        P1 = x;
        delay();
        x = x << 1;           /* shift left */

        if(x == 0)            /* after bit7 falls off, wrap */
            x = 0x01;
    }
}
