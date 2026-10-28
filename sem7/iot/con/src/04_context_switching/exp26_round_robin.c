/* Experiment 26 : Round Robin scheduling with time quantum (delay)
   Each task runs for one quantum then the scheduler moves to next. */
#include "mcu51.h"

unsigned char current = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)      /* one time quantum */
        for(j = 0; j < 1275; j++);
}

void Task1(void) { P1 ^= 0x01; }   /* toggle bit0 */
void Task2(void) { P1 ^= 0x02; }   /* toggle bit1 */
void Task3(void) { P1 ^= 0x04; }   /* toggle bit2 */

void Scheduler(void)
{
    switch(current)
    {
        case 0: Task1(); current = 1; break;
        case 1: Task2(); current = 2; break;
        case 2: Task3(); current = 0; break;   /* round robin */
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
        delay();        /* time quantum - CPU stays with the task */
    }
}
