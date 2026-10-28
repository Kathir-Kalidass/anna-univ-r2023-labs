/*
 * Activity 12: Traffic Light Controller with Timer Delays
 * P1.0=Red, P1.1=Yellow, P1.2=Green
 * Timer 0 for ~2 second delays
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

sbit RED    = P1^0;
sbit YELLOW = P1^1;
sbit GREEN  = P1^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++) ;   /* ~1ms at 11.0592 MHz */
}

void delay_2sec(void) {
    delay_ms(2000);     /* 2000ms = 2 seconds */
}

void all_off(void) {
    RED = 0;
    YELLOW = 0;
    GREEN = 0;
}

void main(void) {
    while (1) {
        /* RED ON (~6 seconds) */
        all_off();
        RED = 1;
        delay_2sec();
        delay_2sec();
        delay_2sec();

        /* GREEN ON (~6 seconds) */
        all_off();
        GREEN = 1;
        delay_2sec();
        delay_2sec();
        delay_2sec();

        /* YELLOW ON (~2 seconds) */
        all_off();
        YELLOW = 1;
        delay_2sec();
    }
}
