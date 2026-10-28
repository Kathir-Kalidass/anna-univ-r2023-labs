/* Experiment 11 : Count number of button presses (shown on P1) */
#include "mcu51.h"

SBIT(SW, 0xB2);   /* P3.2 */

unsigned char count = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 20; i++)
        for(j = 0; j < 1275; j++);   /* debounce */
}

void main(void)
{
    while(1)
    {
        if(SW == 0)
        {
            delay();

            if(SW == 0)
            {
                count++;
                P1 = count;          /* display count in binary */

                while(SW == 0);      /* wait for release */
            }
        }
    }
}
