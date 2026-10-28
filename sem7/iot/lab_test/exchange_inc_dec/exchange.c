#include <8051.h>

__data __at (0x30) unsigned char a;
__data __at (0x31) unsigned char b;
__data __at (0x32) unsigned char temp;

void main(void)
{
    a = 10;
    b = 20;

    temp = a;
    a = b;
    b = temp;

    a++;
    b--;

    while (1);
}
/*
Explanation
1. a = 10, b = 20 — initialize the registers' values (stored here in RAM).
2. temp = a — save the first value.
3. a = b — copy the second value into a.
4. b = temp — complete the exchange.
5. a++ — increment a by 1.
6. b-- — decrement b by 1.
Expected result in MCU 8051 IDE
Inspect internal RAM addresses 30H–32H.
RAM address	Variable	Final value (decimal)	Hex
30H	a	21	15H
31H	b	9	09H
32H	temp	10	0AH
Note: These are RAM variables, not hardware registers R0 and R1. The fixed RAM addresses make the results easier to inspect in the simulator.*/