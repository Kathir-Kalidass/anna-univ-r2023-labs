#include <8051.h>

void main(void)
{
    SCON = 0x50;    /* UART Mode 1, receive enabled */
    TMOD = 0x20;    /* Timer 1, Mode 2 */
    TH1 = 0xFD;     /* 9600 baud at 11.0592 MHz */
    TR1 = 1;        /* Start Timer 1 */

    while (1)
    {
        SBUF = 'A';  /* Transmit character A */
        while (TI == 0);
        TI = 0;

        while (RI == 0);  /* Wait to receive */
        P1 = SBUF;        /* Display received character */
        RI = 0;
    }
}
/*
Explanation
- SCON = 0x50 configures UART Mode 1 with reception enabled.
- TMOD = 0x20 selects Timer 1, Mode 2 (8-bit auto-reload).
- TH1 = 0xFD sets the baud rate to 9600 for a standard 11.0592 MHz clock.
- SBUF = 'A' sends the character A.
- TI becomes 1 when transmission completes; the program clears it.
- RI becomes 1 when a character is received.
- P1 = SBUF writes the received byte to Port 1 for observation.
How to test in MCU 8051 IDE
1. Compile the program and start the simulator.
2. Open the serial/UART terminal if your IDE version provides one.
3. Ensure the serial settings match the program: 9600 baud, 8 data bits, no parity, 1 stop bit (8N1).
4. To test reception, send a character from the terminal.
Important: This program transmits A repeatedly and then waits for a received character. If the terminal does not echo the transmitted character back to the receiver, the program will wait indefinitely. To test both directions, use a serial terminal that can send data to the simulated UART, or connect the real UART TX and RX lines appropriately.*/