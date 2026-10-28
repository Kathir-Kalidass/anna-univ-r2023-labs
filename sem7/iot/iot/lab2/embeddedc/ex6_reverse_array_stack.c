/*
 * Exercise 6: Reverse an Array Using Stack (PUSH/POP)
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

void main(void) {
    unsigned char arr[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    unsigned char i;

    /* Reverse the array in-place (simulating stack PUSH/POP) */
    {
        unsigned char temp;
        unsigned char left = 0;
        unsigned char right = 4;

        while (left < right) {
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }

    /* Display reversed array: P1 shows first element */
    P1 = arr[0];        /* Should show 0x55 */

    while (1);
}
