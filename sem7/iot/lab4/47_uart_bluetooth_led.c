/* HC-05 uses 9600 UART: 'A' ON and 'B' OFF controls P1.0. */
#include "lab4_common.h"
SBIT(LED,0x90);void main(void){unsigned char c;uart_init();while(1){c=uart_getc();if(c=='A')LED=1;if(c=='B')LED=0;}}
