/* Experiment 9 : Switch controls LED
   SW on P3.2  ->  LED on P1.0
   Switch pressed (0) : LED ON  (LED=0)
   Switch released(1) : LED OFF (LED=1)
   (active-low LED on many boards) */
#include "mcu51.h"

SBIT(SW,  0xB2);   /* P3.2 */
SBIT(LED, 0x90);   /* P1.0 */

void main(void)
{
    while(1)
    {
        if(SW == 0)
            LED = 0;   /* pressed  -> LED ON  */
        else
            LED = 1;   /* released -> LED OFF */
    }
}
