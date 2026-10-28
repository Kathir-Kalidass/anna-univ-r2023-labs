/* Output: P1 alternates 55H and AAH. */
#include "lab4_common.h"
void main(void) { while (1) { P1=0x55; delay_ms(300); P1=0xAA; delay_ms(300); } }
