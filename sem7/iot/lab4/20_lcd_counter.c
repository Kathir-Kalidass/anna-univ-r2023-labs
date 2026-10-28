/* INT0/P3.2 increments a 0..255 visitor counter displayed on LCD. */
#include "lab4_common.h"
volatile unsigned char count=0, changed=1;
ISR(count_isr,0) { ++count; changed=1; }
void main(void) { lcd_init(); lcd_puts("Visitors:"); IT0=1; EX0=1; EA=1; while(1) if(changed) { EA=0; changed=0; lcd_cmd(0xC0); lcd_u8(count); EA=1; } }
