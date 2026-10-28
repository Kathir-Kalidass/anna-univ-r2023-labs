/* Send '1' to turn P1.0 ON, '0' OFF, 't' to toggle; reply confirms action. */
#include "lab4_common.h"
SBIT(LED,0x90);
void main(void) { unsigned char c; uart_init(); uart_puts("Commands: 1=ON 0=OFF t=toggle\r\n"); while(1) { c=uart_getc(); if(c=='1'){LED=1;uart_puts("ON\r\n");} else if(c=='0'){LED=0;uart_puts("OFF\r\n");} else if(c=='t'||c=='T'){LED=!LED;uart_puts("TOGGLED\r\n");} } }
