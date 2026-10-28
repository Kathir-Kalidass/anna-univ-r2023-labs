/* Experiment 7 : LED Chase pattern using pattern array */
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 250; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    unsigned char k;
    unsigned char pattern[8] = {0x01, 0x02, 0x04, 0x08,
                                0x10, 0x20, 0x40, 0x80};

    while(1)
    {
        for(k = 0; k < 8; k++)
        {
            P1 = pattern[k];
            delay();
        }
    }
}
