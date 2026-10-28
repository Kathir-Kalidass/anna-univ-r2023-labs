/* Output: P1.0 toggles every 500 ms using Timer0 polling. */
#include "lab4_common.h"
SBIT(LED,0x90);
void main(void) { unsigned char i; while(1) { for(i=0;i<10;i++) timer0_50ms(); LED=!LED; } }
