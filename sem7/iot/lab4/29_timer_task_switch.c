/* Timer0 ISR selects alternating LED/counter task; outputs visible on P1. */
#include "lab4_common.h"
volatile unsigned char task=0, count=0;
ISR(tick_isr,1) { TH0=0x4C; TL0=0; if(++count==2) { count=0; task=!task; } }
void main(void) { TMOD=1; TH0=0x4C; TL0=0; ET0=1; EA=1; TR0=1; while(1) { if(task==0) P1^=0x01; else P1=(P1&0x01)|0x02; delay_ms(100); } }
