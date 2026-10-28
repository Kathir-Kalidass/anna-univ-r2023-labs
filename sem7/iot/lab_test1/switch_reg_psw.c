8051 Embedded C: Switch Between Register Banks Using PSW
Aim: To switch between the four register banks of the 8051 microcontroller by modifying the PSW (Program Status Word) register and observe the values stored in each bank.
Program — SDCC-compatible for MCU 8051 IDE
Since SDCC does not provide R0 as a normal C variable, this program uses fixed internal RAM addresses corresponding to R0 in each bank.
#include <8051.h>

/* R0 address in each register bank */
__data __at (0x00) unsigned char bank0_R0;
__data __at (0x08) unsigned char bank1_R0;
__data __at (0x10) unsigned char bank2_R0;
__data __at (0x18) unsigned char bank3_R0;

void main(void)
{
    /* Select Register Bank 0: RS1=0, RS0=0 */
    PSW = 0x00;
    bank0_R0 = 0x11;

    /* Select Register Bank 1: RS1=0, RS0=1 */
    PSW = 0x08;
    bank1_R0 = 0x22;

    /* Select Register Bank 2: RS1=1, RS0=0 */
    PSW = 0x10;
    bank2_R0 = 0x33;

    /* Select Register Bank 3: RS1=1, RS0=1 */
    PSW = 0x18;
    bank3_R0 = 0x44;

    while (1);
}


Explanation
The 8051 has four register banks, each containing registers R0–R7. The active bank is selected using the RS1 and RS0 bits of PSW.
Register bank	RS1	RS0	RAM addresses	Value stored in R0
Bank 0	0	0	00H–07H	11H
Bank 1	0	1	08H–0FH	22H
Bank 2	1	0	10H–17H	33H
Bank 3	1	1	18H–1FH	44H
PSW register format
CY
7


AC
6


F0
5


RS1
4


RS0
3


OV
2


—
1


P
0



PSW bits 4 and 3 (RS1 and RS0) select the register bank.

- PSW = 00H selects Bank 0.
- PSW = 08H selects Bank 1.
- PSW = 10H selects Bank 2.
- PSW = 18H selects Bank 3.
How to observe the output
1. Compile and run the program.
2. Open the Internal RAM or memory view.
3. Inspect addresses 00H, 08H, 10H, and 18H.
4. You should find 11H, 22H, 33H, and 44H, respectively.
5. Inspect PSW; its final value should be 18H, selecting Bank 3.
Important: This program writes directly to the RAM addresses assigned to each bank. It demonstrates the bank layout and PSW selection, but does not use the C identifier R0 to access the active bank.