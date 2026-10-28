/* Task switching using direct function calls. */
#include "mcu51.h"

void Task1(void)
{
    P1 = 0x0F;
}

void Task2(void)
{
    P1 = 0xF0;
}

void main(void)
{
    while(1)
    {
        Task1();
        Task2();
    }
}
