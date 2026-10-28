/* Read switch on P3.2 and drive LED on P1.0. */
#include "lab4_common.h"

SBIT(SW, 0xB2);   /* P3.2 */
SBIT(LED, 0x90);   /* P1.0 */

void main(void)
{
    LED = 1;

    while(1)
    {
        LED = (SW == 0) ? 0 : 1;
    }
}
