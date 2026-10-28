#include <8051.h>

unsigned char digits[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 3000; i++);
}

void main(void)
{
    unsigned char count = 0;

    P1 = 0xFF;
    P2 = digits[count];

    while (1)
    {
        if (P1_0 == 1)
        {
            delay();

            if (P1_0 == 1)
            {
                count++;

                if (count > 9)
                    count = 0;

                P2 = digits[count];

                while (P1_0 == 1);
                delay();
            }
        }
    }
}