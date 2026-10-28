/* mcu51.h - portable 8051 header (compiles with BOTH Keil C51 and SDCC)
   - Keil:  sbit LED = P1^0;  void isr() interrupt 1;  bit x;
   - SDCC:  __sbit __at(0x90) LED;  void isr() __interrupt(1);  __bit x;
   SBIT(name, addr) : addr = bit address (e.g. P1.0=0x90, P3.2=0xB2)
   ISR(name, vector): vector = interrupt number (0..4)                  */
#ifndef MCU51_H
#define MCU51_H

#include <reg51.h>

#ifdef __SDCC
  #define SBIT(name, addr) __sbit __at(addr) name
  #define ISR(name, vector) void name(void) __interrupt(vector)
  #define BIT __bit
#else
  #define SBIT(name, addr) sbit name = addr
  #define ISR(name, vector) void name(void) interrupt vector
  #define BIT bit
#endif

#endif
