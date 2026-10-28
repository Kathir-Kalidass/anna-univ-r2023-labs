/* Experiment 35 : Context switching - LED task + Switch task
   Task1 : blink LED on P1.0
   Task2 : read switch P3.2, mirror to P1.7
   Scheduler alternates both tasks (cooperative). */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */
SBIT(SW,  0xB2);   /* P3.2 */

unsigned char current = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 200; i++)
        for(j = 0; j < 1275; j++);
}

void LEDTask(void)
{
    LED = !LED;          /* blink */
    delay();
}

void SwitchTask(void)
{
    if(SW == 0)
        P1 = P1 | 0x80;  /* set bit7  */
    else
        P1 = P1 & 0x7F;  /* clear bit7 */
}

void Scheduler(void)
{
    current = (current + 1) % 2;   /* alternate 0 <-> 1 */
}

void main(void)
{
    while(1)
    {
        Scheduler();

        switch(current)
        {
            case 0: LEDTask(); break;
            case 1: SwitchTask(); break;
        }
    }
}
