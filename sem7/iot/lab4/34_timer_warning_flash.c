/* Warning LED P1.0 flashes every 250 ms. */
#include "lab4_common.h"
SBIT(LED,0x90); void main(void) { while(1){delay_ms(250);LED=!LED;} }
