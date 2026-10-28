/* Demo sensor input is P0; sends its decimal value every second. */
#include "lab4_common.h"
void main(void) { unsigned char v;P0=0xFF;uart_init();while(1){v=P0;uart_puts("Sensor=");uart_putc((v/100)+'0');uart_putc(((v/10)%10)+'0');uart_putc((v%10)+'0');uart_puts("\r\n");delay_ms(1000);} }
