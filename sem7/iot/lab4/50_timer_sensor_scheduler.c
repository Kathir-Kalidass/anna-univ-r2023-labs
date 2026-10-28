/* Every 500 ms sample P0 and update P1; useful sensor-scheduling pattern. */
#include "lab4_common.h"
volatile BIT sample=0;volatile unsigned char ticks=0;ISR(t0,1){TH0=0x4C;TL0=0;if(++ticks==10){ticks=0;sample=1;}}
void main(void){P0=0xFF;TMOD=1;TH0=0x4C;TL0=0;ET0=1;EA=1;TR0=1;while(1)if(sample){sample=0;P1=P0;}}
