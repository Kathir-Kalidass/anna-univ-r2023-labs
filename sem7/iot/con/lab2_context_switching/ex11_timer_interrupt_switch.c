/* Lab-2 Ex11 : Timer interrupt based CONTEXT SWITCHING
   Timer0 ISR fires a 5 ms tick and switches between 3 tasks
   (preemptive context switching).
   Task0 : blink LED on P1.0.
   Task1 : read switch P3.2 -> P2.0.
   Task2 : rotate bit pattern on P1.
   On the ISR the hardware saves/restores the CPU context; the
   software switches the task context via `current`. */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 LED */
SBIT(SW,   0xB2);          /* P3.2 switch */
SBIT(SWLed, 0xA0);         /* P2.0 LED */

unsigned char current  = 0;
unsigned char pattern  = 0x01;
unsigned char blinkCtr = 0;

void TaskBlink(void)
{
    blinkCtr++;
    if(blinkCtr >= 100)           /* toggle every 100 ticks (0.5 s) */
    {
        blinkCtr = 0;
        LED1 = (LED1 == 0) ? 1 : 0;
    }
}

void TaskSwitch(void)
{
    if(SW == 0)
        SWLed = 0;
    else
        SWLed = 1;
}

void TaskRotate(void)
{
    P1 = (P1 & 0xFE) | (unsigned char)LED1;
    pattern = pattern << 1;
    if(pattern == 0) pattern = 0x01;
    P1 = pattern;
}

ISR(Timer0ISR, 1)              /* interrupt vector 1 = Timer0 */
{
    TH0 = 0xEC;                /* reload for ~5 ms tick     */
    TL0 = 0x78;
    current = (current + 1) % 3;   /* preemptive context switch */
}

void Scheduler(void)           /* dispatch the selected task */
{
    switch(current)
    {
        case 0: TaskBlink();   break;
        case 1: TaskSwitch();  break;
        case 2: TaskRotate();  break;
    }
}

void main(void)
{
    TMOD = 0x01;               /* Timer0 mode 1, 16-bit */
    TH0 = 0xEC; TL0 = 0x78;
    ET0 = 1;                   /* enable Timer0 interrupt */
    EA  = 1;                   /* enable all interrupts   */
    TR0 = 1;                   /* start timer             */

    while(1)
    {
        Scheduler();           /* run the current task    */
    }
}
