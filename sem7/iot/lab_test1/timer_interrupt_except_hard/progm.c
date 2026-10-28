#include <8051.h>

volatile unsigned char count = 0;

void timer0_isr(void) __interrupt (1)
{
    count++;
    TH0 = 0xFC;
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;     /* Timer 0, Mode 1 */
    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;         /* Enable Timer 0 interrupt */
    EA = 1;          /* Enable global interrupts */
    TR0 = 1;         /* Start Timer 0 */

    while (1);
}
/*
6. Timer Interrupt and External Hardware Interrupt — 8051 Embedded C
(a) Check elapsed time and update a register using Timer 0 interrupt
Aim: Use Timer 0 interrupt to increment a counter whenever the timer overflows.
#include <8051.h>

volatile unsigned char count = 0;

void timer0_isr(void) __interrupt (1)
{
    count++;
    TH0 = 0xFC;
    TL0 = 0x66;
}

void main(void)
{
    TMOD = 0x01;     /* Timer 0, Mode 1 */
    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;         /* Enable Timer 0 interrupt */
    EA = 1;          /* Enable global interrupts */
    TR0 = 1;         /* Start Timer 0 */

    while (1);
}

/*
Explanation
- TMOD = 0x01 configures Timer 0 in 16-bit mode.
- TH0 and TL0 load the timer's starting value.
- ET0 = 1 enables the Timer 0 interrupt.
- EA = 1 enables all permitted interrupts globally.
- TR0 = 1 starts Timer 0.
- Every overflow calls timer0_isr(), which increments count.
Verification: Inspect count in the C variables view. It increases after each timer overflow.
Note: FC66H is a common starting value for approximately 1 ms at a 12 MHz classic 8051 clock. The exact interval depends on the clock frequency and 8051 variant.

(b) Run an ISR when an external hardware interrupt occurs
Aim: Trigger an interrupt when an external input event occurs, then execute an Interrupt Service Routine (ISR).
On a standard 8051, external interrupt 0 uses P3.2 / INT0.
*/
#include <8051.h>

volatile unsigned char key_count = 0;

void external0_isr(void) __interrupt (0)
{
    key_count++;
}

void main(void)
{
    IT0 = 1;     /* INT0: falling-edge triggered */
    EX0 = 1;     /* Enable external interrupt 0 */
    EA = 1;      /* Enable global interrupts */

    while (1);
}

/*
Explanation
- IT0 = 1 configures INT0 to trigger on a falling edge.
- EX0 = 1 enables external interrupt 0.
- EA = 1 enables global interrupts.
- When a falling edge occurs on P3.2, the processor executes external0_isr().
- The ISR increments key_count.
Verification: Trigger the external interrupt input and inspect key_count. It increases once for each detected falling edge.
Important: A keyboard connected to an ordinary port does not automatically trigger an external interrupt. To demonstrate this ISR, connect or configure an interrupt-generating input on P3.2 (INT0). A real keyboard connected through a matrix or ordinary GPIO requires suitable scanning or edge-detection logic.*/