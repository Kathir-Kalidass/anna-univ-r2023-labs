/* Lab-3 Ex6 : Data serialization (A5H on a single pin)
   using CONTEXT SWITCHING
   Task1 : serialize byte 0xA5 - output one bit at a time on P1.7.
   Task2 : timing delay task (gives each bit a fixed bit-time).
   Bit order: MSB first. A running bit on P1.0 shows progress. */
#include "mcu51.h"

SBIT(SER_OUT, 0x97);         /* P1.7 = serial data output */
SBIT(BIT_CLK, 0x90);         /* P1.0 = bit-clock indicator */

#define BYTE_TO_SEND 0xA5

unsigned char bitPos = 0;
unsigned char current = 0;

void TaskSerialize(void)
{
    unsigned char b;

    b = (BYTE_TO_SEND >> (7 - bitPos)) & 0x01;   /* pick next bit */
    SER_OUT = b;                                 /* send the bit  */

    BIT_CLK = (BIT_CLK == 0) ? 1 : 0;            /* toggle clock   */
    bitPos = (bitPos + 1) & 0x07;                /* next bit       */
}

void TaskBitDelay(void)
{
    unsigned int i;
    for(i = 0; i < 2000; i++);                   /* one bit-time    */
}

void Scheduler(void)
{
    current = (current + 1) % 2;

    if(current == 0)
        TaskSerialize();
    else
        TaskBitDelay();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
