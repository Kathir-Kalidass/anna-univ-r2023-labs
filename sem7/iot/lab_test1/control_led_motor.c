8051 Embedded C: Control LED and Motor Using Bit-Addressable RAM
Aim: To control an LED and a motor using individual bits of the 8051's bit-addressable internal RAM.
Program — SDCC-compatible for MCU 8051 IDE
In this program:
- RAM bit 00H controls the LED.
- RAM bit 01H controls the motor.
- P1.0 is connected to the LED.
- P1.1 is connected to the motor driver.
#include <8051.h>

/* Bit-addressable internal RAM */
__sbit __at (0x00) LED_CONTROL;
__sbit __at (0x01) MOTOR_CONTROL;

void main(void)
{
    LED_CONTROL = 0;
    MOTOR_CONTROL = 0;

    while (1)
    {
        /* Turn LED and motor ON */
        LED_CONTROL = 1;
        MOTOR_CONTROL = 1;

        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;

        /* Turn LED OFF and motor ON */
        LED_CONTROL = 0;
        MOTOR_CONTROL = 1;

        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;

        /* Turn LED ON and motor OFF */
        LED_CONTROL = 1;
        MOTOR_CONTROL = 0;

        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;

        /* Turn both OFF */
        LED_CONTROL = 0;
        MOTOR_CONTROL = 0;

        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;
    }
}


Note: This program changes the states very quickly, so you may not see the transitions clearly. Add a delay after each state if you want to observe the LED and motor states in the simulator.
Improved version with delay
#include <8051.h>

__sbit __at (0x00) LED_CONTROL;
__sbit __at (0x01) MOTOR_CONTROL;

void delay(void)
{
    unsigned int i, j;

    for (i = 0; i < 100; i++)
        for (j = 0; j < 1200; j++)
            ;
}

void main(void)
{
    while (1)
    {
        LED_CONTROL = 1;
        MOTOR_CONTROL = 1;
        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;
        delay();

        LED_CONTROL = 0;
        MOTOR_CONTROL = 1;
        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;
        delay();

        LED_CONTROL = 1;
        MOTOR_CONTROL = 0;
        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;
        delay();

        LED_CONTROL = 0;
        MOTOR_CONTROL = 0;
        P1_0 = LED_CONTROL;
        P1_1 = MOTOR_CONTROL;
        delay();
    }
}


Expected output
RAM bit 00H	RAM bit 01H	LED (P1.0)	Motor (P1.1)
1	1	ON	ON
0	1	OFF	ON
1	0	ON	OFF
0	0	OFF	OFF
How to observe the output
1. Compile and run the program in MCU 8051 IDE.
2. Open the C Variables or Internal RAM panel.
3. Inspect RAM byte 20H, which contains bit addresses 00H–07H.
4. Observe P1.0 and P1.1 in the SFR panel or LED virtual hardware.
Important: The RAM bits are software control flags; they do not physically drive hardware. The program copies their values to P1.0 and P1.1. A real motor must be connected through a suitable motor-driver circuit, not directly to an 8051 pin.