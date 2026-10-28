/* Set P0=5AH for unlock (P1.0=1); any other input keeps lock (P1.1=1). */
#include "lab4_common.h"
void main(void) { P0=0xFF; while(1) { if(P0==0x5A) P1=0x01; else P1=0x02; } }
