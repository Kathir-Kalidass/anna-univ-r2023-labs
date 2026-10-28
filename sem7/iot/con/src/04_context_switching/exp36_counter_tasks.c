/* Experiment 36 : Context switching between TWO counter tasks
   Task1 : increments even counter  -> lower nibble of P1
   Task2 : increments odd counter   -> upper nibble of P1
   Alternate execution shows both tasks progressing (multitasking). */
#include "mcu51.h"

unsigned char current  = 0;
unsigned char evenCnt = 0;
unsigned char oddCnt  = 0;

void Task1(void)
{
    evenCnt += 2;                    /* 0,2,4,6,... */
    P1 = (P1 & 0xF0) | (evenCnt & 0x0F);
}

void Task2(void)
{
    oddCnt += 2;                     /* 1,3,5,7,... */
    P1 = (P1 & 0x0F) | ((oddCnt << 4) & 0xF0);
}

void Scheduler(void)
{
    current = (current + 1) % 2;
}

void main(void)
{
    P1 = 0x00;

    while(1)
    {
        Scheduler();

        if(current == 0)
            Task1();
        else
            Task2();
    }
}
