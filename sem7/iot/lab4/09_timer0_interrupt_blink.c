/* Output: P1.0 toggles each 500 ms; observe TF0/interrupts. */
#include "lab4_common.h"
SBIT(LED,0x90); volatile unsigned char ticks=0;
ISR(timer0_isr, 1) { TH0=0x4C; TL0=0x00; if(++ticks==10) { ticks=0; LED=!LED; } }
void main(void) { TMOD=(TMOD&0xF0)|1; TH0=0x4C; TL0=0; ET0=1; EA=1; TR0=1; while(1); }
