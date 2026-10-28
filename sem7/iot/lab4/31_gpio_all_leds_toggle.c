/* P1 alternates FFH/00H: all LEDs toggle together. */
#include "lab4_common.h"
void main(void) { while(1) { P1=0xFF; delay_ms(300); P1=0; delay_ms(300); } }
