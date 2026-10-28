/* Experiment 30 : Context switching using EXTERNAL interrupt INT0 (P3.2)
   Pressing INT0 triggers the ISR which switches between Task1 and Task2. */
#include "mcu51.h"

unsigned char task = 0;

ISR(ext0_isr, 0)
{
    if(task == 0)
    {
        P1 = 0x55;      /* Task1 */
        task = 1;
    }
    else
    {
        P1 = 0xAA;      /* Task2 */
        task = 0;
    }
}

void main(void)
{
    EA  = 1;            /* enable global interrupts */
    EX0 = 1;            /* enable INT0             */
    IT0 = 1;            /* falling-edge triggered   */

    while(1);           /* task switch is done in ISR */
}
