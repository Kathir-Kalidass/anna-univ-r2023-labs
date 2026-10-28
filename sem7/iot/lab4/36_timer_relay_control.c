/* P1.0 relay is ON for 2 s, OFF for 2 s. */
#include "lab4_common.h"
SBIT(RELAY,0x90); void main(void) { while(1){RELAY=1;delay_ms(2000);RELAY=0;delay_ms(2000);} }
