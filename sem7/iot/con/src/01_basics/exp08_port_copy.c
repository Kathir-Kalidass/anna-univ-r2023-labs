/* Experiment 8 : Read Port 0 and display on Port 1 */
#include "mcu51.h"

void main(void)
{
    while(1)
    {
        P1 = P0;   /* copy P0 (input) to P1 (LED) */
    }
}
