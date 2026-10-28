/* Lab-2 Activities Ex3 : Bit-addressable RAM using CONTEXT SWITCHING
   Uses the bit-addressable internal RAM (bytes 0x20-0x2F).
   Task0 : set a bit of byte 0x20 (bit 0x20) from a switch.
   Task1 : clear/complement bit 0x21 and echo both bits to P1.
   Each task works on its own RAM bit - the RAM bytes are the
   saved context shared between tasks. */
#include "mcu51.h"

AT_DATA(ramByte, 0x20);       /* byte 0x20 in bit-addressable RAM */
SBIT_RAM(bitA, 0x20);         /* bit0 of byte 0x20  */
SBIT_RAM(bitB, 0x21);         /* bit1 of byte 0x20  */

SBIT(SW, 0xB2);               /* P3.2 */

unsigned char current = 0;

void TaskSetBitA(void)
{
    if(SW == 0)
        bitA = 1;              /* set bitA from switch  */
    else
        bitA = 0;
}

void TaskBitB(void)
{
    bitB = ~bitB;              /* toggle bitB           */
}

void TaskEcho(void)
{
    P1 = (P1 & 0xFC) | ((unsigned char)bitB << 1) | (unsigned char)bitA;
}

void Scheduler(void)
{
    current = (current + 1) % 3;

    switch(current)
    {
        case 0: TaskSetBitA(); break;
        case 1: TaskBitB();    break;
        case 2: TaskEcho();    break;
    }
}

void main(void)
{
    ramByte = 0;               /* initialise bit RAM */

    while(1)
    {
        Scheduler();
    }
}
