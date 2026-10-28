/* Serial ISR: received byte is copied to P1 and echoed. */
#include "lab4_common.h"
volatile unsigned char received=0;
ISR(serial_isr,4) { if(RI) { received=SBUF; RI=0; P1=received; SBUF=received; } else if(TI) TI=0; }
void main(void) { uart_init(); ES=1; EA=1; uart_puts("Serial ISR ready\r\n"); while(1); }
