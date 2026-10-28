/* Experiment 2 : Turn OFF all LEDs on Port 1 */
#include "mcu51.h"

void main(void)
{
    P1 = 0xFF;   /* 11111111b -> all LEDs OFF */
    while(1);
}
