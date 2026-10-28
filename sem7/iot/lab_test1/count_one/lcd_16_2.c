#include <8051.h>

#define LCD P2

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 3000; i++);
}

void command(unsigned char cmd)
{
    P3 = cmd;
    P1_0 = 0;  /* RS = 0 */
    P1_1 = 0;  /* RW = 0 */
    P1_2 = 1;  /* EN = 1 */
    delay();
    P1_2 = 0;  /* EN = 0 */
}

void display(unsigned char ch)
{
    P3 = ch;
    P1_0 = 1;  /* RS = 1 */
    P1_1 = 0;  /* RW = 0 */
    P1_2 = 1;
    delay();
    P1_2 = 0;
}

void main(void)
{
    command(0x38);  /* 8-bit, 2-line LCD */
    command(0x0C);  /* Display ON */
    command(0x01);  /* Clear display */
    command(0x06);  /* Cursor increment */

    display('H');
    display('E');
    display('L');
    display('L');
    display('O');

    while (1);
}
/*Connections
LCD pin	8051 connection
D0–D7	P3.0–P3.7
RS	P1.0
RW	P1.1
EN	P1.2
VSS, VDD	GND, +5 V
VEE	Contrast control
Expected output: HELLO appears on the first line of the LCD.

Option 1: Interface a 16×2 LCD
Aim: Display HELLO on a 16×2 LCD connected to the 8051.*/