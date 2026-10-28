/* Experiment 39 : UART + LED context switching tasks
   Task1 : transmit "T1" / "T2" on UART (visible in Serial terminal)
   Task2 : toggle LED on P1.0
   Scheduler alternates both tasks.
   Baud setup : 9600 baud using Timer1 Mode 2. */
#include "mcu51.h"

SBIT(LED, 0x90);   /* P1.0 */

unsigned char current = 0;

void UART_Init(void)
{
    TMOD = 0x20;     /* Timer1 Mode 2 (auto reload) */
    TH1  = 0xFD;     /* 9600 baud @ 11.0592 MHz     */
    SCON = 0x50;     /* mode 1, REN enabled         */
    TR1  = 1;
}

void sendChar(unsigned char ch)
{
    SBUF = ch;
    while(TI == 0);
    TI = 0;
}

void sendStr(unsigned char *s)
{
    while(*s)
        sendChar(*s++);
}

void UARTTask(void)
{
    if(current == 0)
        sendStr("T1\n");
    else
        sendStr("T2\n");
}

void LEDTask(void)
{
    LED = !LED;
}

void Scheduler(void)
{
    current = (current + 1) % 2;
}

void main(void)
{
    UART_Init();

    while(1)
    {
        Scheduler();

        switch(current)
        {
            case 0: LEDTask();   break;
            case 1: UARTTask();  break;
        }
    }
}
