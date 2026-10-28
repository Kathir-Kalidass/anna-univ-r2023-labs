/* Output: P1.0 square wave (toggle every 1 ms). */
#include "lab4_common.h"
SBIT(OUT,0x90);
void main(void) { while(1) { timer0_ms(1); OUT=!OUT; } }
