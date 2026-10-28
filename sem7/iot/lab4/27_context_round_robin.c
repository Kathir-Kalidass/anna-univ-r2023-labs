/* Round-robin switching among four outputs. */
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
                task = 1;
                break;

            case 1:
                P1 = 0x02;
                task = 2;
                break;

            case 2:
                P1 = 0x04;
                task = 3;
                break;

            case 3:
                P1 = 0x08;
                task = 0;
                break;
        }
    }
}
