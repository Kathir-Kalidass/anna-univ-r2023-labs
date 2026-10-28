/* Experiment 1 : Turn ON all LEDs on Port 1 */
#include "mcu51.h"

void main(void)
{
    P1 = 0x00;   /* 00000000b -> all LEDs ON (active-low LEDs) */
    while(1);    /* keep LEDs ON forever */
}
