/* Buzzer P1.0 produces a short beep once per second. */
#include "lab4_common.h"
SBIT(BUZZER,0x90); void main(void) { while(1){delay_ms(900);BUZZER=1;delay_ms(100);BUZZER=0;} }
