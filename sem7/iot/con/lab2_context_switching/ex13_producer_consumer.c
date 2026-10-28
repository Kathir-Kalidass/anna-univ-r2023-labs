/* Lab-2 Ex13 : Producer - Consumer using CONTEXT SWITCHING
   Producer task : writes numbers 1..9 into a shared buffer.
   Consumer task : reads the buffer and displays the value on P1.
   The two tasks are synchronised with a "full" flag and switch
   context after each item (classic producer/consumer). */
#include "mcu51.h"

#define BUF_SIZE 8

unsigned char buffer[BUF_SIZE];
unsigned char head = 0, tail = 0, count = 0;
unsigned char item = 1;
unsigned char value = 0;

void Producer(void)
{
    if(count < BUF_SIZE)                 /* space available? */
    {
        buffer[head] = item;             /* produce item     */
        head = (head + 1) % BUF_SIZE;
        count++;
        item++;
        if(item > 9) item = 1;
    }
}

void Consumer(void)
{
    if(count > 0)                        /* item available?  */
    {
        value = buffer[tail];            /* consume item     */
        tail = (tail + 1) % BUF_SIZE;
        count--;
        P1 = value;                      /* show on LEDs     */
    }
}

void Scheduler(void)                     /* alternating context switch */
{
    Producer();
    Consumer();
}

void main(void)
{
    while(1)
    {
        Scheduler();
    }
}
