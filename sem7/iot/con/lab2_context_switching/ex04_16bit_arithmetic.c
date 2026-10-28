/* Lab-2 Ex4 : 16-bit arithmetic using CONTEXT SWITCHING
   Task1 : read a 16-bit number (A = a1:a0 from P2:P0).
   Task2 : 16-bit ADD  (A + B)  -> store sum + carry on LEDs.
   Task3 : 16-bit SUB  (A - B)  -> store diff + borrow on LEDs.
   Context saved/restored around every switch.
   Output: sum LSB on P1, sum MSB on P2, carry  on P3.0
           diff LSB on P1, diff MSB on P2, borrow on P3.1
   (In a real board, B would also come from an input port.) */
#include "mcu51.h"

unsigned char a0, a1;             /* A = a1:a0 */
#define B16 0x1234                /* second number = 0x1234 (4660) */

unsigned char s0, s1, d0, d1;
unsigned char carry = 0, borrow = 0;
unsigned char current = 0;

void TaskRead16(void)
{
    a0 = P0;                      /* A low byte  */
    a1 = P2;                      /* A high byte */
    current = 1;
}

void TaskAdd16(void)
{
    unsigned int sum = ((unsigned int)a1 << 8) + a0 + B16;

    s0 = (unsigned char)sum;      /* sum LSB */
    s1 = (unsigned char)(sum >> 8); /* sum MSB */
    carry = 0;

    if(a1 > 0x7F && (sum & 0x8000) == 0)   /* simple 16-bit overflow note */
        carry = 0;
    if(sum < ((unsigned int)a1 << 8) + a0) /* carry into 17th bit */
        carry = 1;

    P1 = s0;
    P2 = s1;
    P3 = (P3 & 0xFE) | (carry ? 1 : 0);    /* carry LED on P3.0 */
    current = 2;
}

void TaskSub16(void)
{
    long diff = ((long)a1 << 8) + a0 - B16;

    borrow = (diff < 0) ? 1 : 0;
    if(diff < 0) diff = -diff;

    d0 = (unsigned char)diff;     /* diff LSB */
    d1 = (unsigned char)(diff >> 8); /* diff MSB */

    P1 = d0;
    P2 = d1;
    P3 = (P3 & 0xFD) | (borrow ? 2 : 0);   /* borrow LED on P3.1 */
    current = 0;
}

void Scheduler(void)
{
    switch(current)
    {
        case 0: TaskRead16(); break;
        case 1: TaskAdd16();  break;
        case 2: TaskSub16();  break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();       /* context switch between the 3 tasks */
    }
}
