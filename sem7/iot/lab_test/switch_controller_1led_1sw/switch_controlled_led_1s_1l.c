
#include <8051.h>

__sbit __at (0x90) SW;
__sbit __at (0xA7) LED;

void main(void)
{
    P1 = 0xFF;

    while (1)
    {
        LED = SW;
    }
}

/*Step 1: Add the LED panel

1. Click LED Panel in the menu shown in your screenshot.
This may let you connect or observe LEDs through an 8051 port.

2. Add a switch input
Your menu includes Simple Keypad and Matrix Keypad. These are keypad inputs, not necessarily individual switches. Open Simple Keypad first to check its available configuration.



Step 2: Configure the program
Your program uses:
- P1.0 — switch input
- P2.7 — LED output*/