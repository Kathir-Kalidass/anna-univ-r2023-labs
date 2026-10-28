/* task1.c - Task 1 : LED pattern task */
#include "mcu51.h"
#include "tasks.h"

void TaskLED(void)
{
    P1 ^= 0x55;     /* toggle alternate LED pattern */
}
