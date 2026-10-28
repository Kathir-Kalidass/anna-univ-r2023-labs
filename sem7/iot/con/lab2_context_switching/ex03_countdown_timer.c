/* Lab-2 Ex3 : Countdown timer (10 -> 0) using CONTEXT SWITCHING
   Task1 : display countdown 10..0 on P1.
   Task2 : generate the 1-second delay (software loop).
   The two tasks run alternately; each resumes where it stopped
   (count value is kept in a shared "task context" variable). */
#include "mcu51.h"

unsigned char count    = 10;
unsigned char finished = 0;
unsigned char current  = 0;

void Delay1sTask(void)         /* ~1 s software delay */
{
    unsigned int i, j;
    for(i = 0; i < 100; i++)
        for(j = 0; j < 1275; j++);
}

void CountdownTask(void)
{
    P1 = count;                 /* show current count on LEDs */
    Delay1sTask();              /* wait 1 second (as a task)  */

    if(count > 0)
        count--;                /* 10 -> 0 */
    else
        finished = 1;
}

void Scheduler(void)
{
    /* context switch : alternate the two tasks */
    if(current == 0)
    {
        CountdownTask();        /* run task 1 */
        current = 1;
    }
    else
    {
        Delay1sTask();          /* run task 2 (delay) */
        current = 0;
    }
}

void main(void)
{
    P1 = 0xFF;

    while(1)
    {
        Scheduler();
        if(finished)
        {
            P1 = 0x00;          /* reached 0 */
            while(1);           /* stop */
        }
    }
}
