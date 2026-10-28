/* Lab-2 Ex12 : External interrupt based CONTEXT SWITCHING
   Background task : running LED pattern on P1 (continuous).
   Interrupt task   : INT0 (P3.2) - on pressing the external
   interrupt, the CPU hardware saves the background context and
   jumps to the ISR; the ISR saves/restores its own registers,
   then RETI restores the background task exactly where it left.
   LED P1.0 shows "context is being switched" during the ISR. */
#include "mcu51.h"

SBIT(LED1, 0x90);          /* P1.0 */
SBIT(LED2, 0x91);          /* P1.1 */

unsigned char pattern = 0x01;
unsigned int  isrRun  = 0;

void BackgroundTask(void)   /* running LEDs - main context */
{
    P1 = pattern;
    pattern = (pattern << 1);
    if(pattern == 0) pattern = 0x01;
}

ISR(ExtInt0ISR, 0)          /* interrupt vector 0 = INT0 (P3.2) */
{
    unsigned char saved = ACC;   /* save local context */
    P1 = 0xFF;                   /* both LEDs ON = ISR running */
    for(isrRun = 0; isrRun < 20000; isrRun++);
    P1 = 0x00;
    ACC = saved;                 /* restore local context */
}

void main(void)
{
    IT0 = 1;                 /* INT0 on falling edge */
    EX0 = 1;                 /* enable EX0 */
    EA  = 1;                 /* enable all */

    while(1)
    {
        BackgroundTask();    /* background context */
    }
}
