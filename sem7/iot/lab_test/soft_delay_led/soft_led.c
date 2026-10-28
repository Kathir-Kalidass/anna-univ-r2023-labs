#include <8051.h>

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 30000; i++);
}

void main(void)
{
    while (1)
    {
        P1 = 0x01;    /* LED ON */
        delay();

        P1 = 0x00;    /* LED OFF */
        delay();
    }
}
/*Explanation
- delay() uses a for loop to waste CPU cycles, creating a time delay.
- P1 = 0x01 turns ON the LED connected to P1.0.
- P1 = 0x00 turns OFF all LEDs on Port 1.
- while (1) repeats the ON/OFF sequence continuously.
Working
1. LED turns ON.
2. Program waits using the software delay loop.
3. LED turns OFF.
4. Program waits again.
5. The cycle repeats indefinitely.
Expected result: The LED blinks continuously.
Note: The exact delay depends on the 8051 clock frequency and compiler optimization settings. This is a software delay, not a hardware timer delay.*/