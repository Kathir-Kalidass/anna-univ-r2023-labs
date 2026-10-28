#include <8051.h>

__sbit __at (0x90) SW;
__sbit __at (0xA7) LED;

void main(void)
{
    P1 = 0xFF;
    LED = 0;

    while (1)
    {
        if (SW == 0)
        {
            LED = !LED;
            while (SW == 0);
        }
    }
}
/*Working:
- P1.0 — Switch input
- P2.7 — LED output
- Each switch press toggles the LED ON or OFF.
- while (SW == 0); waits until the switch is released.
Note: This assumes an active-low switch connected to ground when pressed.*/