
#include <reg51.h>

sbit SW1 = P1^0;
sbit SW2 = P1^1;

sbit LED1 = P2^0;
sbit LED2 = P2^1;

void main(void)
{
    P1 = 0xFF;       // Configure Port 1 for input

    while (1)
    {
        LED1 = SW1;  // LED1 follows Switch 1
        LED2 = SW2;  // LED2 follows Switch 2
    }
}
