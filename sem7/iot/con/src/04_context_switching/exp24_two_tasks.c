/* Experiment 24 : Context switching between TWO tasks (polling / software)
   Task1 -> P1 = 0x55   Task2 -> P1 = 0xAA
   Sequence : 0x55, 0xAA, 0x55, 0xAA ... */
#include "mcu51.h"

unsigned char task = 0;      /* current task number */

void Task1(void)
{
    P1 = 0x55;               /* 0101 0101 */
}

void Task2(void)
{
    P1 = 0xAA;               /* 1010 1010 */
}

void main(void)
{
    while(1)
    {
        if(task == 0)        /* Task1 is current */
        {
            Task1();
            task = 1;        /* switch to Task2  */
        }
        else                 /* Task2 is current */
        {
            Task2();
            task = 0;        /* switch to Task1  */
        }
    }
}
