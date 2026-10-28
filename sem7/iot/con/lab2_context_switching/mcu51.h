/* mcu51.h - portable 8051 header (compiles with BOTH Keil C51 and SDCC)
   - Keil:  sbit LED = P1^0;  void isr() interrupt 1;  bit x;
   - SDCC:  __sbit __at(0x90) LED;  void isr() __interrupt(1);  __bit x;

   SBIT(name, addr)     : addr = SFR bit address (P1.0=0x90, P3.2=0xB2)
   ISR(name, vector)    : vector = interrupt number (0..4)
   BIT                  : 1-bit variable type
   AT_DATA(name, addr)  : byte variable placed at internal data address
                          (bit-addressable RAM starts at 0x20)
   SBIT_RAM(name, addr) : bit variable placed at internal RAM bit address
                          (byte 0x20 bit0 = address 0x20, ... 0x2F bit7 = 0x7F) */
#ifndef MCU51_H
#define MCU51_H

#include <reg51.h>

#ifdef __SDCC
  #define SBIT(name, addr)    __sbit __at(addr) name
  #define ISR(name, vector)   void name(void) __interrupt(vector)
  #define BIT                 __bit
  #define AT_DATA(name, addr) unsigned char __data __at(addr) name
  #define SBIT_RAM(name, addr) __sbit __at(addr) name
#else
  #define SBIT(name, addr)    sbit name = addr
  #define ISR(name, vector)   void name(void) interrupt vector
  #define BIT                 bit
  #define AT_DATA(name, addr) unsigned char data name _at_ addr
  #define SBIT_RAM(name, addr) sbit name = addr
#endif

#endif
