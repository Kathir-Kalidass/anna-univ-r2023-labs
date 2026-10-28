/* Experiment 42 : Water level controller (application)
   Sensors on P3.0(empty) P3.1(mid) P3.2(full)
   Motor  on P1.0  (0 = pump ON, 1 = pump OFF)
   Buzzer on P1.1  (1 = alarm)
   Logic:
     full  -> pump OFF, no alarm
     mid   -> pump ON
     empty -> pump ON, buzzer alarm
   To test in simulator: change P3 value in the Port 3 window. */
#include "mcu51.h"

SBIT(S_EMPTY, 0xB0);   /* P3.0 = empty sensor */
SBIT(S_MID,   0xB1);   /* P3.1 = mid sensor   */
SBIT(S_FULL,  0xB2);   /* P3.2 = full sensor  */
SBIT(MOTOR,   0x90);   /* P1.0 = pump         */
SBIT(BUZZER,  0x91);   /* P1.1 = alarm        */

void main(void)
{
    MOTOR  = 1;     /* pump OFF initially */
    BUZZER = 0;

    while(1)
    {
        if(S_FULL == 0)              /* tank full  */
        {
            MOTOR  = 1;              /* stop pump  */
            BUZZER = 0;
        }
        else if(S_EMPTY == 0)        /* tank empty */
        {
            MOTOR  = 0;              /* pump ON    */
            BUZZER = 1;              /* alarm      */
        }
        else                         /* mid level  */
        {
            MOTOR  = 0;              /* pump ON    */
            BUZZER = 0;
        }
    }
}
