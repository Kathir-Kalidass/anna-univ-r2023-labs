/* P1.0=red, P1.1=yellow, P1.2=green traffic sequence. */
#include "lab4_common.h"
void main(void) { while(1) { P1=0x01; delay_ms(1000); P1=0x02; delay_ms(300); P1=0x04; delay_ms(1000); } }
