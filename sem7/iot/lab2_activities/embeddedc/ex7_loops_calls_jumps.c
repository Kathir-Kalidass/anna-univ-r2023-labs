/*
 * Activity 7: Loops, Subroutine Calls, and Jumps
 * Demonstrates all major control flow instructions in C equivalents
 * MCUSim 8051 IDE - Embedded C (SDCC compatible)
 */
#include <8051.h>

sbit P1_0 = P1^0;
sbit P1_7 = P1^7;

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 100; i++)
        for (j = 0; j < 200; j++) ;
}

void sub_local(void) {
    P1 = 0xBB;
}

void sub_far(void) {
    P1 = 0xCC;
}

void main(void) {
    unsigned char i;
    unsigned char a, b;

    /* 1. LOOP with DJNZ equivalent */
    for (i = 5; i > 0; i--) {
        P1 = i;
        delay();
    }

    /* 2. JZ / JNZ equivalent */
    a = 0x00;
    if (a == 0) {
        P1 = 0x01;
    }
    delay();

    a = 0x55;
    if (a != 0) {
        P1 = 0x02;
    }
    delay();

    /* 3. JC / JNC equivalent (carry flag) */
    __asm
        CLR C
    __endasm;
    if (PSW & 0x80) {
        P1 = 0x03;
    } else {
        P1 = 0x04;
    }
    delay();

    /* 4. JB / JNB / JBC equivalent */
    P1_0 = 1;
    if (P1_0 == 1) {
        P1 = 0x05;
    }
    delay();

    P1_0 = 0;
    if (P1_0 == 0) {
        P1 = 0x06;
    }
    delay();

    /* JBC: Test and clear */
    P1_7 = 1;
    if (P1_7 == 1) {
        P1_7 = 0;
        P1 = 0x07;
    }
    delay();

    /* 5. CJNE equivalent */
    a = 0x30;
    b = 0x30;
    if (a == b) {
        P1 = 0x08;
    } else if (a < b) {
        P1 = 0x09;
    } else {
        P1 = 0x0A;
    }
    delay();

    a = 0x20;
    b = 0x30;
    if (a < b) {
        P1 = 0x0B;
    } else {
        P1 = 0x0C;
    }
    delay();

    /* 6. SJMP / AJMP / LJMP equivalent */
    goto JMP_DONE;
    P1 = 0xFF;
JMP_DONE:
    P1 = 0x0D;
    delay();

    /* 7. Indirect jump (switch/case) */
    switch (2) {
        case 0: P1 = 0x10; break;
        case 1: P1 = 0x11; break;
        case 2: P1 = 0x12; break;
        case 3: P1 = 0x13; break;
    }
    delay();

    /* 8. ACALL / LCALL / RET */
    sub_local();
    delay();
    sub_far();

    while (1);
}
