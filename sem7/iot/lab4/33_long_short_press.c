/* P0.0 press: P1.0=short, P1.1=long (threshold about 1 second). */
#include "lab4_common.h"
SBIT(SW,0x80);
void main(void) { unsigned char n; P0=0xFF; while(1) if(!SW) { n=0; while(!SW && n<100){delay_ms(10);n++;} P1=(n>=100)?0x02:0x01; while(!SW); } }
