/* Mirror Port1 input to Port2 output. */
#include "mcu51.h"

void main(void)
{
    while(1)
        P2 = P1;
}
