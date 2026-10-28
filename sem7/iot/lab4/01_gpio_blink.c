/* Output: P1.0 repeatedly changes 0/1. */
#include "lab4_common.h"
SBIT(LED, 0x90);
void main(void) { while (1) { LED = !LED; delay_ms(500); } }
