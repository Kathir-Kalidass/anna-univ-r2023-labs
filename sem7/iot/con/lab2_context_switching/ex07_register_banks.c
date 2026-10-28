/* Lab-2 Ex7 : Switch between REGISTER BANKS using CONTEXT SWITCHING
   4 register banks (0..3). Each task owns one bank.
   The bank registers are stored in a 2-D array (saved context).
   Switching: save current bank registers, select next bank by
   writing the RS0/RS1 bits of PSW, restore its saved registers.
   Also demonstrates the register content on P1 (R0 value). */
#include "mcu51.h"

#define NUM_BANKS 4
unsigned char bankReg[NUM_BANKS][8];   /* saved register context */
unsigned char currentBank = 0;
unsigned char value[NUM_BANKS] = {0xAA, 0x55, 0x0F, 0xF0};

void SaveBankRegs(unsigned char b)
{
    unsigned char i;
    unsigned char *rp;
    /* SDCC/Keil don't expose R0..R7 directly, so we store a shadow copy:
       here R0-R7 of the bank are represented by the shadow registers.
       (In real 8051 assembly you would PUSH them.) */
    rp = (unsigned char *)0x08;      /* start of register bank 1  */
    for(i = 0; i < 8; i++)
        bankReg[b][i] = rp[i];       /* save shadow bank to memory */
}

void SelectBank(unsigned char b)
{
    /* select bank b by writing RS0 (bit3) / RS1 (bit4) of PSW */
    PSW = (PSW & 0xE7) | ((b & 0x01) << 3) | ((b & 0x02) << 3);
    currentBank = b;
}

void RestoreBankRegs(unsigned char b)
{
    unsigned char i;
    unsigned char *rp = (unsigned char *)0x08;
    for(i = 0; i < 8; i++)
        rp[i] = bankReg[b][i];
}

void TaskBank(unsigned char b)
{
    SaveBankRegs(currentBank);       /* save old context  */
    SelectBank(b);                   /* PSW switch        */
    RestoreBankRegs(b);              /* restore new task  */
    P1 = value[b];                   /* show task's value */
}

void Scheduler(void)
{
    unsigned char next = (currentBank + 1) % NUM_BANKS;
    TaskBank(next);                  /* context switch to next bank */
}

void main(void)
{
    P1 = 0;

    while(1)
    {
        Scheduler();
    }
}
