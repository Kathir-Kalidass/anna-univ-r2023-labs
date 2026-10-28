/* Lab-3 Ex11 : Timer-based LED blinking + counter
   using CONTEXT SWITCHING
   Task1 : blink an LED on P1.0 every ~1 second.
   Task2 : count seconds and show the count on P0.
   Timer0 interrupt (5 ms tick) drives both the timing and the
   preemptive context switch between the two tasks. */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 */

unsigned char tick    = 0;
unsigned char seconds = 0;
unsigned char current = 0;

void TaskBlinkLED(void)
{
    if((seconds & 0x01) == 0)
        LED1 = 1;               /* ON  for 1 s */
    else
        LED1 = 0;               /* OFF for 1 s */
}

void TaskCounter(void)
{
    P0 = seconds;               /* show elapsed seconds */
}

ISR(Timer0ISR, 1)              /* every 5 ms */
{
    TH0 = 0xEC;
    TL0 = 0x78;

    tick++;
    if(tick >= 200)             /* 200 * 5 ms = 1 second */
    {
        tick = 0;
        seconds++;
    }

    current = (current + 1) % 2;   /* preemptive context switch */
}

void Scheduler(void)
{
    if(current == 0)
        TaskBlinkLED();
    else
        TaskCounter();
}

void main(void)
{
    TMOD = 0x01;               /* Timer0 mode 1 */
    TH0 = 0xEC; TL0 = 0x78;
    ET0 = 1;
    EA  = 1;
    TR0 = 1;

    while(1)
    {
        Scheduler();
    }
}
