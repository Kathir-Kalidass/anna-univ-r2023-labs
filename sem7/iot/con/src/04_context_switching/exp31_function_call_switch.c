/* Experiment 31 : Task switching using simple function calls */
#include "mcu51.h"

void Task1(void)
{
    P1 = 0x0F;      /* 0000 1111 */
}

void Task2(void)
{
    P1 = 0xF0;      /* 1111 0000 */
}

void main(void)
{
    while(1)
    {
        Task1();    /* context switch #1 */
        Task2();    /* context switch #2 */
    }
}
