/* Falling edge on INT0/P3.2 increments visitor count shown on P1. */
#include "lab4_common.h"
volatile unsigned char visitors=0;
ISR(visitor_isr,0) { P1=++visitors; }
void main(void) { P1=0; IT0=1; EX0=1; EA=1; while(1); }
