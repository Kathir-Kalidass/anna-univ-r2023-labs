/* Nested function call stack demonstration. */
#include "mcu51.h"

void Level3(void)
{
    P1 = 0x33;
}

void Level2(void)
{
    Level3();
}

void Level1(void)
{
    Level2();
}

void main(void)
{
    while(1)
        Level1();
}
