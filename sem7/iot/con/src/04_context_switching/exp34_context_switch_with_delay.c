/* Experiment 34 : Context switching WITH delay (visible switching)
   Task1 -> P1 = 0x55 (hold),  switch,  Task2 -> P1 = 0xAA (hold) */
#include "mcu51.h"

unsigned char task = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 1275; j++);
}

void Task1(void)
{
    P1 = 0x55;
    delay();         /* hold Task1 output */
}

void Task2(void)
{
    P1 = 0xAA;
    delay();         /* hold Task2 output */
}

void main(void)
{
    while(1)
    {
        if(task == 0)
        {
            Task1();
            task = 1;        /* context switch */
        }
        else
        {
            Task2();
            task = 0;        /* context switch */
        }
    }
}
