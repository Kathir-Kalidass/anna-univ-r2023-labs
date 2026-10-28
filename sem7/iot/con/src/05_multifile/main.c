/* main.c - RTOS kernel entry point (multi-file context switching)
   Build order in project : all files added to the SAME project. */
#include "mcu51.h"
#include "tasks.h"

void main(void)
{
    TimerInit();             /* start tick timer */

    while(1)
    {
        if(TimerSchedulerTick())   /* a tick occurred ? */
        {
            Scheduler();           /* context switch    */
            ExecuteTask();         /* run next task     */
        }
    }
}
