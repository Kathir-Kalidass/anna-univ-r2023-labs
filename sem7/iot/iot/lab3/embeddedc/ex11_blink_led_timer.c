/*
 * Activity 11: Blink LED at 1-second intervals using Timer 0
 * LED on P1.0, Timer 0 Mode 1, 11.0592 MHz crystal
 * 500ms timer: 65536 - 46080 = 19456 = 4C00H
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

sbit LED = P1^0;

/* Timer 0 ISR - toggles LED every 500ms */
void timer0_isr(void) __interrupt(1) {
    TH0 = 0x4C;        /* Reload timer high */
    TL0 = 0x00;        /* Reload timer low */
    LED = !LED;         /* Toggle LED */
}

void main(void) {
    TMOD = 0x01;        /* Timer 0, Mode 1 (16-bit) */
    TH0 = 0x4C;         /* 500ms delay value high */
    TL0 = 0x00;         /* 500ms delay value low */
    ET0 = 1;             /* Enable Timer 0 interrupt */
    EA = 1;              /* Enable global interrupts */
    TR0 = 1;             /* Start Timer 0 */

    while (1);          /* LED toggles via ISR */
}
