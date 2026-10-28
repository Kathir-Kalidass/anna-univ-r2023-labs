8051 Embedded C: Countdown Counter (10 to 0)
Aim: To display a countdown from 10 to 0 with a 1-second delay between each number using the 8051 simulator.
Program — SDCC-compatible for MCU 8051 IDE
This version displays the count on Port 2 (P2) in binary. For a numeric display from 10 to 0, use the 7-segment version below.
#include <8051.h>

unsigned char count;
unsigned int i, j;

void delay(void)
{
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 1200; j++)
        {
            ;
        }
    }
}

void main(void)
{
    for (count = 10; count > 0; count--)
    {
        P2 = count;
        delay();
    }

    P2 = 0;
    while (1);
}


Note: The delay loop is approximate and depends on the clock frequency and compiler optimization. It may not be exactly one second.
Expected output on P2
Count	P2 value (hex)	Binary
10	0AH	00001010
9	09H	00001001
8	08H	00001000
…	…	…
1	01H	00000001
0	00H	00000000
To display the numbers on a 7-segment display
If your virtual 7-segment display is connected to P2.0–P2.7, use this version instead. It assumes an active-high, common-cathode display.
#include <8051.h>

unsigned char digits[11] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F,
    0x00
};

unsigned char count;
unsigned int i, j;

void delay(void)
{
    for (i = 0; i < 100; i++)
        for (j = 0; j < 1200; j++)
            ;
}

void main(void)
{
    count = 10;

    while (1)
    {
        P2 = digits[count];
        delay();

        if (count == 0)
            break;

        count--;
    }

    while (1);
}


How to view the output
1. Open the virtual hardware panel and select the 7-segment display.
2. Ensure segments a through g are mapped to P2.0–P2.6.
3. Compile and run the program.
4. The display should show 10, 9, 8, …, 1, 0, with an approximate one-second delay.
Important: A single 7-segment display cannot show the two digits of 10 simultaneously. To display 10 properly, use a two-digit display or two separate 7-segment displays.