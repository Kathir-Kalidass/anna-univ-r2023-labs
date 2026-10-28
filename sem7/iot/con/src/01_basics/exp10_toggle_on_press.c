/* Experiment 10 : Toggle LED on every switch press (with debounce) */
#include "mcu51.h"

SBIT(SW,  0xB2);   /* P3.2 */
SBIT(LED, 0x90);   /* P1.0 */

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 30; i++)
        for(j = 0; j < 1275; j++);   /* ~10 ms debounce */
}

void main(void)
{
    LED = 1;

    while(1)
    {
        if(SW == 0)              /* pressed ? */
        {
            delay();             /* debounce */

            if(SW == 0)          /* confirm still pressed */
            {
                LED = !LED;      /* toggle LED */

                while(SW == 0);  /* wait for release */
            }
        }
    }
}
