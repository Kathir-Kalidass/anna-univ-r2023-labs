/* UART reports P0.0 switch state once per second. */
#include "lab4_common.h"
SBIT(SW,0x80); void main(void) { P0=0xFF;uart_init();while(1){uart_puts(!SW?"SWITCH PRESSED\r\n":"SWITCH RELEASED\r\n");delay_ms(1000);} }
