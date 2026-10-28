/* Experiment 4 : Alternate LED pattern 01010101 <-> 10101010 */
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 400; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    while(1)
    {
        P1 = 0x55;   /* 0101 0101 */
        delay();
        P1 = 0xAA;   /* 1010 1010 */
        delay();
    }
}
