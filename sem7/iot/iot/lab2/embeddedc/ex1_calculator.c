/*
 * Exercise 1: Calculator with Subroutines
 * Choice=1: ADD, 2: SUB, 3: MUL, 4: DIV, 5: EXIT
 * MCUSim 8051 IDE - Embedded C
 */
#include <8051.h>

/* Subroutine: Addition */
unsigned char add(unsigned char a, unsigned char b) {
    return a + b;
}

/* Subroutine: Subtraction */
unsigned char sub(unsigned char a, unsigned char b) {
    return a - b;
}

/* Subroutine: Multiplication */
unsigned char mul(unsigned char a, unsigned char b) {
    return a * b;
}

/* Subroutine: Division */
unsigned char div_op(unsigned char a, unsigned char b) {
    if (b != 0)
        return a / b;
    return 0;
}

void main(void) {
    unsigned char num1 = 25;
    unsigned char num2 = 10;
    unsigned char choice = 3;   /* Change choice: 1=ADD,2=SUB,3=MUL,4=DIV */
    unsigned char result = 0;

    switch (choice) {
        case 1:
            result = add(num1, num2);
            break;
        case 2:
            result = sub(num1, num2);
            break;
        case 3:
            result = mul(num1, num2);
            break;
        case 4:
            result = div_op(num1, num2);
            break;
        case 5:
            /* Exit - do nothing */
            break;
        default:
            break;
    }

    P1 = result;    /* Display result on Port 1 */

    while (1);      /* Stop here */
}
