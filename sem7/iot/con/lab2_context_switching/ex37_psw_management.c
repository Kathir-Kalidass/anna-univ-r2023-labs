/* Lab-2 Activities Ex5 : PSW register management during CONTEXT SWITCHING
   Three tasks, one per register bank. During every context switch:
   - save the current PSW,
   - restore the PSW of the next task (activating its register bank),
   - resume execution where the task was interrupted.
   The active bank is shown on P1 (0x01=bank0, 0x02=bank1, 0x04=bank2). */
#include "mcu51.h"

#define NUM_TASKS 3

unsigned char savedPSW[NUM_TASKS];   /* per-task PSW (bank) */
unsigned char current = 0;

void TaskBank0(void) { P1 = 0x01; }
void TaskBank1(void) { P1 = 0x02; }
void TaskBank2(void) { P1 = 0x04; }

void Scheduler(void)
{
    unsigned char psw = PSW;

    savedPSW[current] = psw;         /* 1. save current PSW  */

    current = (current + 1) % NUM_TASKS;

    PSW = savedPSW[current];         /* 2. restore next PSW  */

    switch(current)                  /* 3. resume the task   */
    {
        case 0: TaskBank0(); break;
        case 1: TaskBank1(); break;
        case 2: TaskBank2(); break;
    }
}

void main(void)
{
    savedPSW[0] = 0x00;              /* bank 0 : RS1=0 RS0=0 */
    savedPSW[1] = 0x08;              /* bank 1 : RS1=0 RS0=1 */
    savedPSW[2] = 0x10;              /* bank 2 : RS1=1 RS0=0 */

    while(1)
    {
        Scheduler();
    }
}
