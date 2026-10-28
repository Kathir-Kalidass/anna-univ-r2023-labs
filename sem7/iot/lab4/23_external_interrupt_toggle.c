/* Press/int0 falling edge at P3.2: P1.0 toggles. */
#include "lab4_common.h"
SBIT(LED,0x90);
ISR(int0_isr,0) { LED=!LED; }
void main(void) { IT0=1; EX0=1; EA=1; while(1); }
