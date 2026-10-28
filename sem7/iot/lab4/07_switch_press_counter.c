/* Press P0.0: increment binary count shown at P1. */
#include "lab4_common.h"
SBIT(SW, 0x80);
void main(void) { unsigned char count=0; P0=0xFF; P1=0; while(1) if(!SW) { delay_ms(20); if(!SW) { P1=++count; while(!SW); } } }
