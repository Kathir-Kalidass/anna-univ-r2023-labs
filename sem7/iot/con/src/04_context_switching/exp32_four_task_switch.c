/* Experiment 32 : Four-task context switching (round robin)
   Sequence : 0x01, 0x02, 0x04, 0x08, 0x01, ... */
#include "mcu51.h"

unsigned char task = 0;

void main(void)
{
    while(1)
    {
        switch(task)
        {
            case 0:
                P1 = 0x01;
                task++;
                break;

            case 1:
                P1 = 0x02;
                task++;
                break;

            case 2:
                P1 = 0x04;
                task++;
                break;

            case 3:
                P1 = 0x08;
                task = 0;       /* wrap around */
                break;
        }
    }
}
