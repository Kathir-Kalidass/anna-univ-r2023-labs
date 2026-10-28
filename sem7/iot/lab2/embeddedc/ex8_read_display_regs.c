/*
 * Exercise 8: Read and Display P0, P1, ACC, B, PSW, SP, DPTR
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char val;

    /* Read and display P0 on P1 */
    val = P0;
    P1 = val;

    /* Read and display P1 on P2 */
    val = P1;
    P2 = val;

    /* Display ACC value on P1 */
    ACC = 0x55;
    P1 = ACC;

    /* Display B register on P2 */
    B = 0xAA;
    P2 = B;

    /* Display PSW on P1 */
    val = PSW;
    P1 = val;

    /* Display SP on P2 */
    val = SP;
    P2 = val;

    /* Display DPTR on P1 and P2 */
    DPTR = 0x1234;
    P1 = DPH;          /* High byte on P1 */
    P2 = DPL;          /* Low byte on P2 */

    /* Continuous read and display loop */
    while (1) {
        P1 = PSW;      /* P1 = PSW continuously */
        P2 = SP;       /* P2 = SP continuously */
    }
}
