/* Experiment 3 : Blink all LEDs on Port 1 */
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    while(1)
    {
        P1 = 0x00;   /* LEDs ON  */
        delay();     /* wait */
        P1 = 0xFF;   /* LEDs OFF */
        delay();     /* wait */
    }
}
