/* Portable 8051 definitions: SDCC in MCU 8051 IDE and Keil C51. */
#ifndef MCU51_H
#define MCU51_H
#include <reg51.h>
#ifdef __SDCC
#define SBIT(name, address) __sbit __at(address) name
#define ISR(name, vector) void name(void) __interrupt(vector)
#define BIT __bit
#else
#define SBIT(name, address) sbit name = address
#define ISR(name, vector) void name(void) interrupt vector
#define BIT bit
#endif
#endif
