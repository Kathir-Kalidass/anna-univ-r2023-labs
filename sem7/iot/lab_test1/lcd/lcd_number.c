#include <8051.h>

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 30000; i++);
}

void lcd_cmd(unsigned char cmd)
{
    P2 = cmd;
    P1_0 = 0;
    P1_1 = 0;
    P1_2 = 1;
    delay();
    P1_2 = 0;
}

void lcd_char(unsigned char ch)
{
    P2 = ch;
    P1_0 = 1;
    P1_1 = 0;
    P1_2 = 1;
    delay();
    P1_2 = 0;
}

void main(void)
{
    unsigned char i;

    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x80);

    while (1)
    {
        for (i = 0; i < 10; i++)
        {
            lcd_char('0' + i);
            delay();
        }

        lcd_cmd(0x01);
        lcd_cmd(0x80);
    }
}

/*1. Configure the LCD pins
In the LCD window, use the dropdowns under PORT and BIT to select the connections.
Use this mapping:
LCD signal	Port	Bit
RS	P1	0
R/W	P1	1
E	P1	2
D7	P2	7
D6	P2	6
D5	P2	5
D4	P2	4
D3	P2	3
D2	P2	2
D1	P2	1
D0	P2	0
For each signal, select the port in the PORT row and the pin number in the BIT row. If the LCD component uses a different ordering for the dropdowns, follow the labels shown above each column.
2. Use the LCD program
Your original digits[] program is for a 7-segment display. For this LCD, use the LCD command/data program below instead.
#include <8051.h>

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 30000; i++);
}

void lcd_cmd(unsigned char cmd)
{
    P2 = cmd;
    P1_0 = 0;
    P1_1 = 0;
    P1_2 = 1;
    delay();
    P1_2 = 0;
}

void lcd_char(unsigned char ch)
{
    P2 = ch;
    P1_0 = 1;
    P1_1 = 0;
    P1_2 = 1;
    delay();
    P1_2 = 0;
}

void main(void)
{
    unsigned char i;

    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x80);

    while (1)
    {
        for (i = 0; i < 10; i++)
        {
            lcd_char('0' + i);
            delay();
        }

        lcd_cmd(0x01);
        lcd_cmd(0x80);
    }
}


3. Run and verify
1. Compile the program with SDCC.
2. Start the simulation.
3. Ensure the LCD's ON indicator is enabled.
4. The LCD should display 01234567, then 89, before clearing and repeating.
Important: Your LCD window labels the data pins in the order D7 through D0. The code writes a complete byte to P2, so each data pin must be mapped to its matching P2 bit. If the display remains blank, send a screenshot after you select the dropdown values; I can check the mapping.*/