/* INT0/P3.2 count displayed on P1. */
#include "lab4_common.h"
volatile unsigned char n=0;ISR(i0,0){P1=++n;}void main(void){IT0=1;EX0=1;EA=1;while(1);}
