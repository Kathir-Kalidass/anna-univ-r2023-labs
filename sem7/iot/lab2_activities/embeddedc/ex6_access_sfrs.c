/*
 * Activity 6: Access SFRs (80H-FFH) and Print Values
 * Reads key SFRs and displays on P1/P2 for verification
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 150; i++)
        for (j = 0; j < 200; j++) ;
}

void main(void) {
    unsigned char val;

    /* P0 (Address 80H) */
    val = P0;
    P1 = val;
    delay();

    /* P1 (Address 90H) */
    P1 = 0xAA;
    val = P1;
    P2 = val;
    delay();

    /* P2 (Address 0A0H) */
    P2 = 0x55;
    val = P2;
    P1 = val;
    delay();

    /* P3 (Address 0B0H) */
    val = P3;
    P1 = val;
    delay();

    /* ACC (Address 0E0H) */
    ACC = 0xC3;
    P1 = ACC;
    delay();

    /* B Register (Address 0F0H) */
    B = 0xA5;
    P1 = B;
    delay();

    /* PSW (Address 0D0H) */
    val = PSW;
    P1 = val;
    delay();

    /* SP (Address 81H) */
    val = SP;
    P1 = val;
    delay();

    /* DPTR (DPH=83H, DPL=82H) */
    DPTR = 0x1234;
    P1 = DPH;              /* P1 = 12H */
    delay();
    P1 = DPL;              /* P1 = 34H */
    delay();

    /* TMOD (Address 89H) */
    TMOD = 0x01;
    P1 = TMOD;             /* P1 = 01H */
    delay();

    /* TCON (Address 88H) */
    val = TCON;
    P1 = val;
    delay();

    /* TH0 / TL0 */
    TH0 = 0xFF;
    TL0 = 0x00;
    P1 = TH0;              /* P1 = FFH */
    delay();
    P1 = TL0;              /* P1 = 00H */
    delay();

    /* SCON (Address 98H) */
    val = SCON;
    P1 = val;
    delay();

    /* IE (Address 0A8H) */
    val = IE;
    P1 = val;
    delay();

    /* IP (Address 0B8H) */
    val = IP;
    P1 = val;

    while (1);
}
