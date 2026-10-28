#include <reg51.h>

#define D  P1
#define RS P3_0
#define RW P3_1
#define E  P3_2

void write_lcd(unsigned char val) {
    E = 1;
    D = val;
    E = 0;
}

void main(void) {
    const char *str = "Hello World!";
    const char *ptr;

    D = 0;
    RW = 0;

    while (1) {

        RS = 0;
        write_lcd(0x01); 
        write_lcd(0x80);  


        RS = 1;
        ptr = str;
        while (*ptr != '\0') {
            write_lcd(*ptr);
            ptr++;
        }
    }
}


8051 LCD Interfacing — Detailed MCU 8051 IDE Configuration
Your program is intended to display Hello World! on an LCD using the 8051 microcontroller. Since you are using MCU 8051 IDE with SDCC, there are two important things to configure: the LCD virtual hardware pins and the LCD control sequence.
1. LCD pin configuration
Your code defines these connections:
#define D  P1
#define RS P3_0
#define RW P3_1
#define E  P3_2


Configure the LCD virtual hardware window as follows.
LCD signal	8051 port pin	Purpose
RS	P3.0	0 = command, 1 = character data
R/W	P3.1	0 = write to LCD
E	P3.2	Enable signal
D7	P1.7	Data bit 7
D6	P1.6	Data bit 6
D5	P1.5	Data bit 5
D4	P1.4	Data bit 4
D3	P1.3	Data bit 3
D2	P1.2	Data bit 2
D1	P1.1	Data bit 1
D0	P1.0	Data bit 0
In your LCD virtual hardware window, use the dropdowns below PORT and BIT to map each signal to the corresponding port and pin. Enable the LCD using its ON control.
2. Important correction to your code
Your current write_lcd() function only changes the data and enable pins. It does not generate a proper enable pulse with a delay, and the program does not initialize the LCD. Also, repeatedly sending 0x01 clears the display every time through the infinite loop.
For the 1 × 8 LCD component shown in your IDE, use this SDCC-compatible version:
#include <8051.h>

#define D  P1
#define RS P3_0
#define RW P3_1
#define E  P3_2

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 3000; i++);
}

void write_lcd(unsigned char val)
{
    D = val;
    E = 1;
    delay();
    E = 0;
    delay();
}

void lcd_cmd(unsigned char cmd)
{
    RS = 0;
    RW = 0;
    write_lcd(cmd);
}

void lcd_data(unsigned char ch)
{
    RS = 1;
    RW = 0;
    write_lcd(ch);
}

void main(void)
{
    const char *str = "Hello World!";
    const char *ptr;

    D = 0x00;
    RS = 0;
    RW = 0;
    E = 0;

    delay();

    lcd_cmd(0x38);  /* 8-bit interface, 2-line mode */
    lcd_cmd(0x0C);  /* Display ON, cursor OFF */
    lcd_cmd(0x01);  /* Clear display */
    lcd_cmd(0x06);  /* Increment cursor */

    lcd_cmd(0x80);  /* First character position */

    ptr = str;
    while (*ptr != '\0')
    {
        lcd_data(*ptr);
        ptr++;
    }

    while (1);
}


3. Run the program in MCU 8051 IDE
1. Open the C file and compile it. Fix any errors before continuing.
2. Open Virtual HW → LCD Display and configure the pin mapping above.
3. Make sure the LCD virtual component is switched ON.
4. Start the simulator and execute the program.
5. Observe the LCD display.
Expected text: Hello W on the 8-character display, with the remaining characters beyond the visible positions depending on the LCD component's behavior.
4. Important limitation
Your IDE screenshot showed a 1 × 8 LCD, which has only eight visible character positions. Therefore, it cannot display the full 12-character string Hello World! at once. To display the complete message simultaneously, use a 16 × 2 LCD component if your IDE provides one.
Also, 0x38 configures a standard HD44780-compatible LCD for an 8-bit, two-line interface. If the virtual LCD component behaves differently, its configuration and initialization requirements may need adjustment.


