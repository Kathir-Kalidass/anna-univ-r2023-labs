/* Output: LED sweeps P1.0..P1.7 then back. */
#include "lab4_common.h"
void main(void) { unsigned char x; while (1) { for(x=1;x;x<<=1){P1=x;delay_ms(100);} for(x=0x40;x;x>>=1){P1=x;delay_ms(100);} } }
