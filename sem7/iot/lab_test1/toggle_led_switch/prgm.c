#include <8051.h>

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 3000; i++);
}

void main(void)
{
    unsigned char state = 0;

    P3 = 0xFF;
    P1 = 0x00;

    while (1)
    {
        if ((P3 & 0x01) == 0)
        {
            delay();

            if ((P3 & 0x01) == 0)
            {
                state = !state;
                P1 = state;

                while ((P3 & 0x01) == 0);
                delay();
            }
        }
    }
}
/*Explanation
- P3.0: Switch input (active-low; pressed means 0).
- P1.0: LED output.
- delay() reduces switch-bounce effects.
- state = !state changes the LED state between 0 and 1.
- The while loop waits for the switch to be released, so one press causes only one toggle.
Expected output
Switch action	LED
First press	ON
Second press	OFF
Third press	ON
Fourth press	OFF
Note: This assumes an active-low switch and an active-high LED. If your switch is connected to a different P3 pin, change the bit mask 0x01 accordingly.*/