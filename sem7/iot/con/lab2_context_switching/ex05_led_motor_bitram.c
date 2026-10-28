/* Lab-2 Ex5 : LED and Motor control using CONTEXT SWITCHING
   Both devices are driven by bits of the bit-addressable internal
   RAM (byte at 0x20). Each bit is an independent "task output".
   Task1 : LED control  (bit0 of RAM 0x20 -> P1.0)
   Task2 : Motor control(bit1 of RAM 0x20 -> P1.1)
   Scheduler alternates the tasks; RAM bits = saved context. */
#include "mcu51.h"

AT_DATA(deviceRAM, 0x20);      /* bit-addressable byte in internal RAM */
SBIT_RAM(ledBit,   0x20);      /* bit0 of byte 0x20 -> LED   */
SBIT_RAM(motorBit, 0x21);      /* bit1 of byte 0x20 -> Motor */

SBIT(SW_LED,   0xB0);          /* P3.0 = LED switch   */
SBIT(SW_MOTOR, 0xB1);          /* P3.1 = Motor switch */

unsigned char current = 0;

void LEDTask(void)
{
    if(SW_LED == 0)
        ledBit = 1;             /* set LED bit in RAM  */
    else
        ledBit = 0;

    P1 = (P1 & 0xFE) | (unsigned char)ledBit;   /* RAM bit -> P1.0 */
}

void MotorTask(void)
{
    if(SW_MOTOR == 0)
        motorBit = 1;           /* set motor bit in RAM */
    else
        motorBit = 0;

    P1 = (P1 & 0xFD) | ((unsigned char)motorBit << 1);  /* -> P1.1 */
}

void Scheduler(void)
{
    current = (current + 1) % 2;   /* context switch */

    if(current == 0)
        LEDTask();
    else
        MotorTask();
}

void main(void)
{
    deviceRAM = 0;               /* initialise bit-addressable RAM */

    while(1)
    {
        Scheduler();
    }
}
