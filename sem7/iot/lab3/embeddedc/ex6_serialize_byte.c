/*
 * Activity 6: Serialize data byte A5H through single output pin
 * Sends each bit of A5H serially through P1.0 (LSB first)
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

sbit SERIAL_PIN = P1^0;

void bit_delay(void) {
    unsigned int i;
    for (i = 0; i < 200; i++) ;
}

void main(void) {
    unsigned char data_val = 0xA5;   /* 10100101b */
    unsigned char i;
    unsigned char mask;

    mask = 0x01;    /* Start with LSB */

    for (i = 0; i < 8; i++) {
        if (data_val & mask)
            SERIAL_PIN = 1;          /* Send bit 1 */
        else
            SERIAL_PIN = 0;          /* Send bit 0 */
        bit_delay();                 /* Bit period delay */
        mask = mask << 1;            /* Next bit */
    }

    SERIAL_PIN = 0;                  /* Line idle low */

    while (1);
}
