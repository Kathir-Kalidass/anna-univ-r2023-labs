/* task2.c - Task 2 : switch reading task (P3.2 -> P2.0) */
#include "mcu51.h"
#include "tasks.h"

void TaskSwitch(void)
{
    if((P3 & 0x04) == 0)      /* P3.2 pressed? */
        P2 = P2 | 0x01;
    else
        P2 = P2 & 0xFE;
}
