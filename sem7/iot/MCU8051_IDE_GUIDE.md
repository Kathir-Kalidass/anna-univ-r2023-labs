# MCU 8051 IDE - Procedure Guide
## How to Setup, Build, Simulate and View Outputs

---

## 1. INSTALLATION

### MCU 8051 IDE (includes SDCC compiler)
```
Linux:   sudo apt install mcu8051ide
Windows: Download from https://github.com/pfalcon/MCU8051IDE
```

### SDCC Compiler (required by MCU 8051 IDE)
```
Linux:   sudo apt install sdcc
Windows: Download from http://sdcc.sourceforge.net
```

Open MCU 8051 IDE, go to **Tools > Compiler Configuration**
Set SDCC path: `/usr/bin/sdcc` (Linux) or `C:\Program Files\SDCC\bin\sdcc.exe` (Windows)

---

## 2. CREATE A NEW PROJECT

1. **File > New Project**
2. Save as `myproject.8051` (choose a folder)
3. IDE creates project structure automatically

---

## 3. ADD A SOURCE FILE

### For Embedded C (.c):
1. **File > New File**
2. Write your C code (or paste)
3. **File > Save As** -> name it `main.c`
4. In Project Explorer (left panel), right-click **Source Files**
5. **Add Existing File** -> select `main.c`

### For Assembly (.asm):
1. **File > New File**
2. Write ASM code
3. **File > Save As** -> name it `main.asm`
4. Add to Source Files the same way

---

## 4. SELECT TARGET MCU

1. **Project > Target MCU Configuration**
2. Select: **AT89C51** or **AT89C52** (most common)
3. Crystal Frequency: **11.0592 MHz** (standard for 8051)
4. Click OK

---

## 5. BUILD / COMPILE

- **Build > Build** (or press **F9**)
- Check the **Output Window** at bottom for errors
- If 0 errors, a `.ihx` (Intel Hex) file is generated
- **Build > Clean** to remove old build files

### Common errors:
| Error | Fix |
|-------|-----|
| `undefined symbol _crol_` | Replace `_crol_(x,n)` with `(x << n) \| (x >> (8-n))` |
| `undefined P1_0` | Add `sbit P1_0 = P1^0;` after `#include` |
| `_asm` syntax error | Change to `__asm` / `__endasm` (SDCC syntax) |
| `interrupt` error | Change to `__interrupt(n)` |

---

## 6. SIMULATE / RUN

### Load the program:
1. **Simulator > Load Code File**
2. Select the generated `.ihx` file (in project folder)
3. Or: **Build > Auto-load after build** (enable this)

### Run simulation:
1. **Simulator > Run** (or press **F5**)
2. **Simulator > Stop** (or press **Shift+F5**)
3. **Simulator > Reset** to restart
4. **Simulator > Step Into** (F7) - step one instruction
5. **Simulator > Step Over** (F8) - step over subroutine calls

---

## 7. VIEW OUTPUTS - PORT / LED DISPLAY

### Method 1: Internal LEDs (Built-in)
MCU 8051 IDE has built-in **LED Display** panel:
1. **View > Show Port LEDs** (or toolbar icon)
2. Shows P0, P1, P2, P3 as 8 LEDs each
3. LEDs turn ON/OFF automatically as ports change

### Method 2: Using External LEDs (in code)
Connect LEDs to ports. In the simulator:
1. **Peripherals > I/O Ports > Port 1**
2. Shows hex value and individual bit states
3. You can manually toggle input bits (switches)

### Method 3: LED Display Window
1. **View > LED Display**
2. Configurable LED matrix
3. Set port address and bit mapping

---

## 8. VIEW SPECIAL FUNCTION REGISTERS (SFRs)

### Watch Window:
1. **View > Watch Window**
2. Add variables: right-click > **Add Watch**
3. Type register name: `P1`, `P2`, `ACC`, `PSW`, `SP`, `DPTR`, `TMOD`, `TH0`, `TL0`

### SFR Viewer:
1. **Peripherals > SFR Viewer**
2. Shows all SFRs with current values
3. Click any SFR to expand bit-level view

### Memory Viewer:
1. **View > Internal Memory**
2. Shows RAM 00H-FFH
3. Type address to jump: `0x20` for bit-addressable area

---

## 9. VIEW PORT VALUES (LED OUTPUT)

### Step-by-step to see LED output:

```
Example: P1 = 0xA5 (10100101)
LEDs:     P1.7=ON  P1.6=OFF P1.5=ON  P1.4=OFF
          P1.3=OFF P1.2=OFF P1.1=ON  P1.0=OFF
```

1. Build and load your program
2. Open **Peripherals > I/O Ports > Port 1**
3. Run the program
4. Watch the port value change in real-time
5. Each bit = 1 means LED ON, bit = 0 means LED OFF

### For switch input:
1. Open **Peripherals > I/O Ports > Port 0**
2. Click individual bits to toggle switch state (0/1)
3. Your code reads P0 and updates P1 accordingly

---

## 10. TIMER / INTERRUPT VIEWING

### Timer View:
1. **Peripherals > Timers > Timer 0**
2. Shows TMOD, TH0, TL0, TR0, TF0
3. Watch the timer count up in real-time
4. See when overflow interrupt fires

### Interrupt View:
1. **Peripherals > Interrupts**
2. Shows IE register, interrupt flags
3. Watch ISR execution

---

## 11. COMPLETE WORKFLOW EXAMPLE

### Blink LED on P1.0 using Timer 0:

```c
#include <8051.h>
sbit LED = P1^0;

void timer0_isr(void) __interrupt(1) {
    TH0 = 0x4C;
    TL0 = 0x00;
    LED = !LED;
}

void main(void) {
    TMOD = 0x01;
    TH0 = 0x4C;
    TL0 = 0x00;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
    while (1);
}
```

Steps:
1. Paste code -> Save as `blink.c`
2. Add to project -> Build (F9)
3. Simulator > Load Code -> select `.ihx`
4. View > Watch Window -> add `P1`, `TH0`, `TL0`
5. Peripherals > Timers > Timer 0
6. Run (F5) -> Watch LED toggle on Port 1 view
7. LED should toggle every ~500ms (1 second blink)

---

## 12. SDCC COMPATIBILITY CHEAT SHEET

| Keil Syntax | SDCC Syntax | Notes |
|-------------|-------------|-------|
| `_crol_(x,n)` | `(x << n) \| (x >> (8-n))` | Rotate left |
| `_cror_(x,n)` | `(x >> n) \| (x << (8-n))` | Rotate right |
| `_asm ... _endasm` | `__asm ... __endasm` | Inline assembly |
| `interrupt 1` | `__interrupt(1)` | ISR declaration |
| `sbit P1_0 = P1^0;` | `sbit P1_0 = P1^0;` | Same (both supported) |
| `#include <reg51.h>` | `#include <8051.h>` | Header file |
| `P1_0` (implicit) | Must declare `sbit P1_0 = P1^0;` | SDCC has no implicit bit names |

---

## 13. LED WIRING REFERENCE (for real hardware)

```
8051 Pin  ->  LED Anode (+) -> Resistor (220-470 ohm) -> GND
P1.0 pin  ->  LED1
P1.1 pin  ->  LED2
...
P1.7 pin  ->  LED8

Active HIGH: SETB P1.0 turns LED ON
Active LOW:  CLR P1.0 turns LED ON (if wired active-low)
```

### Switch Wiring:
```
VCC ---[10K Pull-up]---+--- P0.x pin
                        |
                    [Switch]
                        |
                       GND

Switch pressed  = P0.x reads 0 (active low)
Switch released = P0.x reads 1
```

---

## 14. QUICK REFERENCE - KEYBOARD SHORTCUTS

| Action | Shortcut |
|--------|----------|
| Build | F9 |
| Run | F5 |
| Stop | Shift+F5 |
| Step Into | F7 |
| Step Over | F8 |
| Reset | Ctrl+F5 |
| Save | Ctrl+S |
| Undo | Ctrl+Z |

---

## 15. TROUBLESHOOTING

| Problem | Solution |
|---------|----------|
| LEDs don't show output | Make sure **View > LED Display** or **Peripherals > I/O Ports** is open |
| Timer not counting | Check `TR0=1` is set; check TMOD mode is correct |
| ISR never executes | Check `EA=1` (global interrupt enable) and `ET0=1` (timer interrupt enable) |
| Port reads all 0s | Set port to input first: `P0 = 0xFF;` before reading |
| Build error on `sbit` | Make sure `#include <8051.h>` is at the top |
| Simulation too fast | Increase delay loop counts or timer reload values |
| Build error `_crol_` | Replace with bitwise shift: `(x << n) \| (x >> (8-n))` |
