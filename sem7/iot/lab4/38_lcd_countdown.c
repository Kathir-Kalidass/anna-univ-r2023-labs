/* LCD countdown from 30 to 00, then repeats. */
#include "lab4_common.h"
void main(void) { signed char n; lcd_init(); lcd_puts("Countdown:"); while(1) for(n=30;n>=0;n--){lcd_cmd(0xC0);lcd_u8((unsigned char)n);delay_ms(1000);} }
