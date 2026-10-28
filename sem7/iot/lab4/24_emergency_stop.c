/* P1.0 normally blinks. INT0/P3.2 emergency switch stops it and sets P1.1. */
#include "lab4_common.h"
SBIT(RUN_LED,0x90); SBIT(ALARM,0x91); volatile BIT stopped=0;
ISR(stop_isr,0) { stopped=1; RUN_LED=0; ALARM=1; }
void main(void) { IT0=1; EX0=1; EA=1; while(1) { if(!stopped) { RUN_LED=!RUN_LED; delay_ms(300); } } }
