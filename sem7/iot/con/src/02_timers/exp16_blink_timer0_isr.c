/* Experiment 16 : Blink LED using Timer0 INTERRUPT (no polling)
   Timer0 Mode 1.  On every overflow the ISR toggles LED and reloads timer. */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

ISR(timer0_isr, 1)
{
    LED = !LED;      /* toggle LED  */

    TH0 = 0xFC;      /* reload timer */
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;     /* Timer0 Mode 1 */

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;         /* enable Timer0 interrupt */
    EA  = 1;         /* enable global interrupt */

    TR0 = 1;         /* start Timer0 */

    while(1);        /* main does nothing */
}
