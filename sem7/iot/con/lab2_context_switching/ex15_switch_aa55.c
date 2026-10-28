/* Lab-3 Ex1 : Switch-controlled LED pattern (AAH / 55H)
   using CONTEXT SWITCHING
   Task1 : monitor switch P3.2 (read it into a shared variable).
   Task2 : display 0xAA or 0x55 on P1 depending on the switch.
   Scheduler alternates the two tasks; shared variable = context. */
#include "mcu51.h"

SBIT(SW, 0xB2);               /* P3.2 */

unsigned char swState = 0;
unsigned char current = 0;

void TaskMonitorSwitch(void)
{
    if(SW == 0)
        swState = 1;          /* switch pressed  */
    else
        swState = 0;
}

void TaskDisplayPattern(void)
{
    if(swState)
        P1 = 0xAA;            /* pressed  -> AAH */
    else
        P1 = 0x55;            /* released -> 55H */
}

void Scheduler(void)
{
    current = (current + 1) % 2;

    if(current == 0)
        TaskMonitorSwitch();
    else
        TaskDisplayPattern();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
