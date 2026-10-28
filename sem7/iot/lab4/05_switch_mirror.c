/* Input: P0 switch bank. Output: identical bit pattern on P1. */
#include "lab4_common.h"
void main(void) { P0=0xFF; while (1) P1=P0; }
