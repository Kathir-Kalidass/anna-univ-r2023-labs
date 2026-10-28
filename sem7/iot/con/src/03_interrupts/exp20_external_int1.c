/* Experiment 20 : External interrupt INT1 (P3.3) toggles all P1 LEDs */
#include "mcu51.h"

ISR(ext1_isr, 2)
{
    P1 = ~P1;   /* toggle all LEDs */
}

void main(void)
{
    EA  = 1;
    EX1 = 1;    /* enable INT1 */
    IT1 = 1;    /* falling edge triggered */

    while(1);
}
