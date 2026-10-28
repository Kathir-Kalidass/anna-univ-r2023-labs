/* Water level controller with simulated sensors on P3.0-P3.2. */
#include "mcu51.h"

SBIT(S_EMPTY, 0xB0);
SBIT(S_MID,   0xB1);
SBIT(S_FULL,  0xB2);
SBIT(MOTOR,   0x90);
SBIT(BUZZER,  0x91);

void main(void)
{
    MOTOR = 1;
    BUZZER = 0;

    while(1)
    {
        if(S_FULL == 0)
        {
            MOTOR = 1;
            BUZZER = 0;
        }
        else if(S_EMPTY == 0)
        {
            MOTOR = 0;
            BUZZER = 1;
        }
        else
        {
            MOTOR = 0;
            BUZZER = 0;
        }
    }
}
