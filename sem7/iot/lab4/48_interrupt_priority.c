/* INT0 has high priority; Timer0 ISR toggles P1.0, INT0 toggles P1.1. */
#include "lab4_common.h"
SBIT(TICK_LED,0x90);SBIT(INT_LED,0x91);
ISR(int0_isr,0){INT_LED=!INT_LED;} ISR(t0_isr,1){TH0=0x4C;TL0=0;TICK_LED=!TICK_LED;}
void main(void){TMOD=1;TH0=0x4C;TL0=0;IT0=1;PX0=1;EX0=1;ET0=1;EA=1;TR0=1;while(1);}
