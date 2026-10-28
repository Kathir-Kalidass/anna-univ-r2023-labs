/* task3.c - Task 3 : counter task (displayed on P0) */
#include "mcu51.h"
#include "tasks.h"

static unsigned char cnt = 0;

void TaskCounter(void)
{
    cnt++;
    P0 = cnt;
}
