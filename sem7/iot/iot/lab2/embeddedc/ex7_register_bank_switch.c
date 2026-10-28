/*
 * Exercise 7: Switch Between Register Banks Using PSW
 * Demonstrates register bank switching via PSW manipulation
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char psw_val;

    /* Bank 0: RS1=0, RS0=0 (default) */
    /* Using xdata or idata variables to simulate bank usage */

    /* Read and display current PSW */
    psw_val = PSW;
    P1 = psw_val;       /* Display PSW on P1 */

    /* Modify PSW to switch to Bank 1 (RS0=1) */
    PSW = PSW | 0x08;   /* Set RS0 bit -> Bank 1 */
    psw_val = PSW;
    P2 = psw_val;       /* Display modified PSW on P2 */

    /* Switch to Bank 2 (RS1=1, RS0=0) */
    PSW = (PSW & 0xE7) | 0x10;  /* Clear RS0, set RS1 -> Bank 2 */
    psw_val = PSW;
    P1 = psw_val;

    /* Switch to Bank 3 (RS1=1, RS0=1) */
    PSW = PSW | 0x18;   /* Set both RS1 and RS0 -> Bank 3 */
    psw_val = PSW;
    P2 = psw_val;

    /* Switch back to Bank 0 */
    PSW = PSW & 0xE7;   /* Clear RS1 and RS0 -> Bank 0 */
    psw_val = PSW;
    P1 = psw_val;

    while (1);
}
