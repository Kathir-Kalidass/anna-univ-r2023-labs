/* Experiment 23 : Interrupt controlled LED - INT0 starts/stops blinking,
   Timer0 provides the blink rate. */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */
BIT running = 0;   /* 0 = stopped, 1 = running */

ISR(ext0_isr, 0)
{
    running = !running;      /* start / stop blinking */

    if(running)
        TR0 = 1;             /* start timer */
    else
    {
        TR0 = 0;             /* stop timer  */
        LED = 1;             /* LED OFF    */
    }
}

ISR(timer0_isr, 1)
{
    LED = !LED;

    TH0 = 0xFC;
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;       /* timer interrupt   */
    EX0 = 1;       /* INT0 interrupt    */
    EA  = 1;
    IT0 = 1;

    while(1);
}
