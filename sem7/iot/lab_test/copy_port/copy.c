#include <8051.h>

void main(void)
{
    unsigned char data;

    while (1)
    {
        data = P1;   /* Read input from Port 1 */
        P2 = data;   /* Write output to Port 2 */
    }
}
/*Explanation
- data = P1; reads the 8-bit input from Port 1.
- P2 = data; copies that value to Port 2.
- while (1) continuously reads and updates the output.
Example
Port 1 input	Port 2 output
00000001	00000001
00000101	00000101
11110000	11110000
Expected result: The output at Port 2 follows the input at Port 1.
Note: For the standard 8051, write P1 = 0xFF; before the loop to release Port 1's pins for input use.*/