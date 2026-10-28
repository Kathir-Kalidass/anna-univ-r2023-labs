/* Watch SP: ACC is saved/restored with PUSH/POP direct addresses. */
#include "lab4_common.h"
void change_acc(void) { __asm push 0xe0 __endasm; ACC=0x55; P1=ACC; __asm pop 0xe0 __endasm; }
void main(void) { SP=0x2F; ACC=0xA5; change_acc(); P1=ACC; while(1); }
