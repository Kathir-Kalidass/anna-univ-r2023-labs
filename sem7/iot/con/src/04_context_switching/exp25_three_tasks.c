/* Experiment 25 : Context switching among THREE tasks
   Sequence : 0x11, 0x22, 0x44, 0x11, 0x22, 0x44 ... */
#include "mcu51.h"

unsigned char task = 0;

void main(void)
{
    while(1)
    {
        switch(task)
        {
            case 0:
                P1 = 0x11;      /* Task 1 */
                task = 1;
                break;

            case 1:
                P1 = 0x22;      /* Task 2 */
                task = 2;
                break;

            case 2:
                P1 = 0x44;      /* Task 3 */
                task = 0;       /* back to Task 1 */
                break;
        }
    }
}
