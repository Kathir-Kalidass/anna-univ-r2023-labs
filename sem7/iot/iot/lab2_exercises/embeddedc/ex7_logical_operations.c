/*
 * Exercise 7: AND, OR, XOR Logical Operations
 * Num1=0xC5 at mem[0], Num2=0x6D at mem[1]
 * AND result at mem[2], OR at mem[3], XOR at mem[4]
 * Display XOR result on P1
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 200; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char data mem[5];

    mem[0] = 0xC5;             /* Num1 */
    mem[1] = 0x6D;             /* Num2 */

    mem[2] = mem[0] & mem[1];  /* AND result */
    mem[3] = mem[0] | mem[1];  /* OR result  */
    mem[4] = mem[0] ^ mem[1];  /* XOR result */

    /* Cycle through results on P1 for verification */
    P1 = mem[2];               /* Display AND result */
    delay();
    P1 = mem[3];               /* Display OR result */
    delay();
    P1 = mem[4];               /* Display XOR result */

    while (1);
}
