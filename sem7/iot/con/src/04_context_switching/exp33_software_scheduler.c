/* Experiment 33 : Software scheduler (scheduler counter selects task)
   Sequence : 0x10, 0x20, 0x40, 0x10, ... */
#include "mcu51.h"

unsigned char scheduler = 0;

void main(void)
{
    while(1)
    {
        scheduler++;

        if(scheduler == 1)
            P1 = 0x10;

        else if(scheduler == 2)
            P1 = 0x20;

        else if(scheduler == 3)
        {
            P1 = 0x40;
            scheduler = 0;
        }
    }
}
