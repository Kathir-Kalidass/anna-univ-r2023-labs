/* Output: P1.0 changes every one second using Timer1 Mode 1. */
#include "lab4_common.h"
SBIT(LED,0x90);
void main(void) { unsigned char i; TMOD=(TMOD&0x0F)|0x10; while(1) { for(i=0;i<20;i++){TH1=0x4C;TL1=0;TF1=0;TR1=1;while(!TF1);TR1=0;TF1=0;} LED=!LED; } }
