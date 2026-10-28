/* Lab-2 Activities Ex9 : Register bank based CONTEXT SWITCHING (4 banks)
   Task1 -> Register Bank 0
   Task2 -> Register Bank 1
   Task3 -> Register Bank 2
   Task4 -> Register Bank 3
   During every context switch the PSW is saved/restored to
   activate the correct register bank. Active bank on P1:
   0x01, 0x02, 0x04, 0x08. */
#include "mcu51.h"

#define NUM_TASKS 4

unsigned char savedPSW[NUM_TASKS];
unsigned char current = 0;

void TaskBank0(void) { P1 = 0x01; }
void TaskBank1(void) { P1 = 0x02; }
void TaskBank2(void) { P1 = 0x04; }
void TaskBank3(void) { P1 = 0x08; }

void Scheduler(void)
{
    unsigned char psw = PSW;

    savedPSW[current] = psw;         /* save current PSW */

    current = (current + 1) % NUM_TASKS;

    PSW = savedPSW[current];         /* restore next PSW  */

    switch(current)
    {
        case 0: TaskBank0(); break;
        case 1: TaskBank1(); break;
        case 2: TaskBank2(); break;
        case 3: TaskBank3(); break;
    }
}

void main(void)
{
    savedPSW[0] = 0x00;              /* bank 0 */
    savedPSW[1] = 0x08;              /* bank 1 */
    savedPSW[2] = 0x10;              /* bank 2 */
    savedPSW[3] = 0x18;              /* bank 3 */

    while(1)
    {
        Scheduler();
    }
}
