8051 Embedded C: Arithmetic Operations Using Subroutines
Aim: To repeatedly check a control variable (choice) and perform addition, subtraction, multiplication, or division using separate subroutines. The program exits when choice = 5.
Program — SDCC-compatible for MCU 8051 IDE
#include <8051.h>

unsigned char a = 20;
unsigned char b = 5;
unsigned char choice = 1;

unsigned int result;
unsigned char remainder;

/* Addition subroutine */
void addition(void)
{
    result = a + b;
}

/* Subtraction subroutine */
void subtraction(void)
{
    result = a - b;
}

/* Multiplication subroutine */
void multiplication(void)
{
    result = (unsigned int)a * b;
}

/* Division subroutine */
void division(void)
{
    if (b != 0)
    {
        result = a / b;
        remainder = a % b;
    }
}

/* Main program */
void main(void)
{
    while (1)
    {
        switch (choice)
        {
            case 1:
                addition();
                choice = 2;
                break;

            case 2:
                subtraction();
                choice = 3;
                break;

            case 3:
                multiplication();
                choice = 4;
                break;

            case 4:
                division();
                choice = 5;
                break;

            case 5:
                while (1);
                break;

            default:
                choice = 5;
                break;
        }
    }
}


Explanation
Choice	Operation	Result for a = 20, b = 5
1	Addition	25
2	Subtraction	15
3	Multiplication	100
4	Division	Quotient = 4, remainder = 0
5	Exit	Program stops performing operations
- Subroutines: addition(), subtraction(), multiplication(), and division() implement the four operations separately.
- switch: Selects the operation based on choice.
- while (1): Repeatedly checks the control variable.
- result: Stores the arithmetic result. Inspect it in the IDE's C Variables window.
Important: This version automatically changes choice from 1 to 5 to demonstrate all four operations in sequence. To test individual choices manually, remove the assignments that change choice and modify the global variable using the debugger.

Steps to view the output
1. Compile your C program and fix any errors.
2. Load/run the program in the simulator.
3. Open View → C Variables (or the corresponding C Variables panel in your IDE).
4. Locate these variables:
   - a = 20
   - b = 5
   - choice = current operation
   - result = arithmetic result
   - remainder = division remainder
5. Run or single-step the program and inspect result after each operation.
Expected output
choice	Operation	result
1	Addition	25
2	Subtraction	15
3	Multiplication	100
4	Division	4
The earlier program automatically changes choice from 1 to 5, so the final value of result will be 4, and choice will become 5.
Note: If the simulator runs continuously, it may be difficult to observe each intermediate result. Use single-step execution or set breakpoints inside each subroutine.
If you want to see the result physically on the virtual hardware, I can modify the program to display the result on the LED panel or 7-segment display.