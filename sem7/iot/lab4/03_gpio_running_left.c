/* Output: one-hot LED pattern moves P1.0 to P1.7. */
#include "lab4_common.h"
void main(void) { unsigned char x; while (1) for (x=1; x; x<<=1) { P1=x; delay_ms(120); } }
