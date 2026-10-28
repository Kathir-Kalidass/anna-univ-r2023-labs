/* Apply pulses to T0=P3.4. Output: low 8-bit pulse count on P1. */
#include "lab4_common.h"
void main(void) { TMOD=(TMOD&0xF0)|0x05; TH0=0; TL0=0; TR0=1; while(1) P1=TL0; }
