Stack Operations (PUSH and POP) in 8051 Embedded C
Aim: To demonstrate stack memory operations, PUSH and POP, using the 8051 microcontroller and SDCC in MCU 8051 IDE.
Program
#include <8051.h>

void main(void)
{
    SP = 0x2F;       /* Initialize stack pointer */

    ACC = 0x25;
    B = 0x36;

    _asm
        PUSH 0xE0    /* Push ACC onto stack */
        PUSH 0xF0    /* Push B register onto stack */

        POP 0x30     /* Pop top value into RAM 30H */
        POP 0x31     /* Pop next value into RAM 31H */
    _endasm;

    while (1);
}


Explanation
- SP = 0x2F initializes the stack pointer to internal RAM address 2FH.
- ACC = 0x25 loads the accumulator with 25H.
- B = 0x36 loads the B register with 36H.
- PUSH 0xE0 pushes the accumulator onto the stack.
- PUSH 0xF0 pushes the B register onto the stack.
- POP 0x30 removes the top stack value and stores it at RAM address 30H.
- POP 0x31 removes the next value and stores it at RAM address 31H.
Expected result
RAM address	Value	Explanation
30H	36H	Value popped from B
31H	25H	Value popped from ACC
SP	2FH	Returns to its original value
Important stack concept
The 8051 stack follows LIFO (Last In, First Out):
- The last value pushed is the first value popped.
- PUSH increments SP before storing data.
- POP reads data from the current SP and then decrements SP.
SDCC note: _asm ... _endasm syntax may depend on the compiler configuration. If your SDCC build rejects this code, I can provide an equivalent pure Embedded C version using a software stack array, or a version using SDCC inline assembly syntax supported by your setup.