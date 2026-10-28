/* Lab-3 Ex15 : Register-bank based CONTEXT SWITCHING (3 tasks)
   Three tasks, each using its own register bank 0/1/2.
   Task switching: save old bank registers, select the next bank
   via the RS0/RS1 bits of PSW, restore its registers.
   PSW is saved/restored explicitly as the CPU context. */
#include "mcu51.h"

unsigned char bankReg[3][8];   /* saved register context per bank */
unsigned char currentBank = 0;
unsigned char ledValue[3] = {0xAA, 0x55, 0x0F};

void SaveContext(void)          /* save current task context (PSW+ACC) */
{
    /* RS0/RS1 in PSW identify the current bank */
    bankReg[currentBank][4] = PSW;   /* save PSW in slot 4 */
    bankReg[currentBank][5] = ACC;   /* save ACC in slot 5 */
    bankReg[currentBank][6] = B;     /* save B   in slot 6 */
}

void SelectBank(unsigned char b)
{
    unsigned char psw = PSW;
    psw = (psw & 0xE7) | ((b & 0x01) << 3) | ((b & 0x02) << 3);
    PSW = psw;                       /* switch register bank */
    currentBank = b;
}

void RestoreContext(void)
{
    PSW = bankReg[currentBank][4];   /* restore saved context */
    ACC = bankReg[currentBank][5];
    B   = bankReg[currentBank][6];
}

void Task0(void) { P1 = ledValue[0]; }
void Task1(void) { P1 = ledValue[1]; }
void Task2(void) { P1 = ledValue[2]; }

void Scheduler(void)                 /* context switch to next bank */
{
    unsigned char next = (currentBank + 1) % 3;

    SaveContext();                   /* save current task context */

    SelectBank(next);                /* PSW: select bank 'next' */

    switch(next)                     /* run the selected task   */
    {
        case 0: Task0(); break;
        case 1: Task1(); break;
        case 2: Task2(); break;
    }
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
