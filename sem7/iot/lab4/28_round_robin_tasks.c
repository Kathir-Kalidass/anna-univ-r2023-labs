/* Cooperative two-task simulation: P1.0 toggles and P1.1 advances a count. */
#include "lab4_common.h"
SBIT(LED,0x90); unsigned char count=0;
void task_led(void) { LED=!LED; }
void task_counter(void) { P1=(P1&0x01)|(count++<<1); }
void main(void) { while(1) { task_led(); delay_ms(100); task_counter(); delay_ms(100); } }
