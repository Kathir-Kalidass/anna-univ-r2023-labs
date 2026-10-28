/* Press active-low P0.0: P1.0 toggles once per press. */
#include "lab4_common.h"
SBIT(SW, 0x80); SBIT(LED, 0x90);
void main(void) { P0=0xFF; while(1) if(!SW) { delay_ms(20); if(!SW) { LED=!LED; while(!SW); delay_ms(20); } } }
