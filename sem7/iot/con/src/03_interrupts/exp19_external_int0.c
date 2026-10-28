/* Experiment 19 : External interrupt INT0 (P3.2) toggles LED on P1.0
   IT0=1 -> falling-edge triggered. */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

ISR(ext0_isr, 0)
{
    LED = !LED;
}

void main(void)
{
    EA  = 1;   /* enable global interrupts */
    EX0 = 1;   /* enable INT0             */
    IT0 = 1;   /* edge triggered          */

    while(1);  /* wait for interrupts     */
}
