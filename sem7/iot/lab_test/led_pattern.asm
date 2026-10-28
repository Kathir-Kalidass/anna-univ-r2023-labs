#include <8051.h>

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 30000; i++);
}

void main(void)
{
    unsigned char LED = 0x01;

    while (1)
    {
        P1 = LED;
        delay();
        LED = LED << 1;

        if (LED == 0)
            LED = 0x01;
    }
}