8051 Embedded C: Reverse an Array Using Stack (PUSH/POP)
Aim: To reverse an array using the 8051 stack by pushing array elements onto the stack and popping them in reverse order.
Since you're using MCU 8051 IDE with SDCC, the program below uses SDCC-compatible C and explicitly accesses the 8051 stack pointer (SP).
Program
#include <8051.h>

unsigned char arr[5] = {10, 20, 30, 40, 50};
unsigned char rev[5];
unsigned char i;

void main(void)
{
    SP = 0x5F;  /* Initialize stack pointer */

    /* PUSH: Store array elements on stack */
    for (i = 0; i < 5; i++)
    {
        SP++;
        *((__data unsigned char *)SP) = arr[i];
    }

    /* POP: Retrieve elements in reverse order */
    for (i = 0; i < 5; i++)
    {
        rev[i] = *((__data unsigned char *)SP);
        SP--;
    }

    while (1);
}


Explanation
1. Initialize stack: SP = 0x5F sets the stack pointer to internal RAM address 5FH.
2. Push elements: Each array element is copied to the next stack location.
3. Pop elements: Elements are read from the top of the stack, producing the reverse order.
4. Store output: The reversed array is saved in rev.
Expected output
Index	Original array (arr)	Reversed array (rev)
0	10	50
1	20	40
2	30	30
3	40	20
4	50	10
Important note about actual 8051 PUSH and POP
The program above simulates stack operations through RAM access; it does not execute the actual PUSH direct and POP direct instructions.
If your practical requires the real 8051 stack instructions, use assembly or SDCC inline assembly. The hardware stack grows upward: PUSH increments SP before storing, and POP reads from the current SP before decrementing it.