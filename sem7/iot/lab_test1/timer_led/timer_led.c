#include <8051.h>

void delay(void)
{
    unsigned int i;

    for (i = 0; i < 100; i++)
    {
        TF0 = 0;
        TH0 = 0xFC;
        TL0 = 0x66;

        TR0 = 1;
        while (TF0 == 0);
        TR0 = 0;
    }
}

void main(void)
{
    TMOD = 0x01;     /* Timer 0, Mode 1 */
    P1 = 0x00;

    while (1)
    {
        P1 = P1 ^ 0x01;  /* Toggle P1.0 */
        delay();
    }
}
/*
Explanation
- TMOD = 0x01 configures Timer 0 in 16-bit mode.
- TH0 = 0xFC and TL0 = 0x66 load the timer for approximately 1 ms at a 12 MHz classic 8051 clock.
- TR0 = 1 starts the timer.
- while (TF0 == 0); waits until timer overflow.
- TR0 = 0 stops the timer.
- The delay function repeats this process 100 times, giving approximately 100 ms.
- P1 = P1 ^ 0x01 toggles P1.0 between ON and OFF.
Expected result
The LED connected to P1.0 blinks continuously, with approximately 100 ms between toggles.
Note: The actual delay depends on the oscillator frequency and 8051 variant. For a classic 12 MHz 8051, each timer increment takes approximately 1 µs.*/