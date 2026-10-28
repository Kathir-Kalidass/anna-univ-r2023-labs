/* Experiment 41 : Traffic light controller (application)
   P1.0 = Red, P1.1 = Yellow, P1.2 = Green
   Sequence : Red 5 s -> Yellow 1 s -> Green 4 s -> repeat */
#include "mcu51.h"

SBIT(RED,    0x90);   /* P1.0 = Red    */
SBIT(YELLOW, 0x91);   /* P1.1 = Yellow */
SBIT(GREEN,  0x92);   /* P1.2 = Green  */

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 200; j++);   /* ~1 ms inner loop */
}

void main(void)
{
    while(1)
    {
        RED    = 0;   YELLOW = 1;  GREEN = 1;   /* Red ON  */
        delay_ms(5000);

        RED    = 1;   YELLOW = 0;  GREEN = 1;   /* Yellow  */
        delay_ms(1000);

        RED    = 1;   YELLOW = 1;  GREEN = 0;   /* Green   */
        delay_ms(4000);
    }
}
