/* Experiment 13 : Arithmetic operations (+, -, *, /, %) displayed on ports */
#include "mcu51.h"

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 200; i++)
        for(j = 0; j < 1275; j++);
}

void main(void)
{
    unsigned char x = 25, y = 10;

    while(1)
    {
        P1 = x + y;   /* 25+10 = 35   = 0x23 */
        delay();
        P1 = x - y;   /* 25-10 = 15   = 0x0F */
        delay();
        P1 = x * y;   /* 25*10 = 250  = 0xFA */
        delay();
        P1 = x / y;   /* 25/10 = 2    = 0x02 */
        delay();
        P1 = x % y;   /* 25%10 = 5    = 0x05 */
        delay();
    }
}
