/* Experiment 38 : Sensor + LED context switching tasks
   Task1 : read sensor value (simulated on P2) -> display on P0
   Task2 : blink LEDs on P1
   Scheduler alternates both tasks. */
#include "mcu51.h"

unsigned char current = 0;

void delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 200; i++)
        for(j = 0; j < 1275; j++);
}

void SensorTask(void)
{
    P0 = P2;         /* copy sensor input to P0 */
}

void LEDTask(void)
{
    P1 = ~P1;        /* toggle all LEDs */
    delay();
}

void Scheduler(void)
{
    current = (current + 1) % 2;
}

void main(void)
{
    while(1)
    {
        Scheduler();

        switch(current)
        {
            case 0: SensorTask(); break;
            case 1: LEDTask();    break;
        }
    }
}
