; Activity 6: Access SFRs (80H-FFH) and Print Values
; Reads key SFRs and displays their values on P1/P2

        ORG     0000H

MAIN:
        ;----- P0 (Port 0, Address 80H) -----
        MOV     A, P0           ; Read P0
        MOV     P1, A           ; Display P0 on P1
        ACALL   DELAY

        ;----- P1 (Port 1, Address 90H) -----
        MOV     P1, #0AAH       ; Write known value to P1
        MOV     A, P1           ; Read back P1
        MOV     P2, A           ; Display on P2
        ACALL   DELAY

        ;----- P2 (Port 2, Address 0A0H) -----
        MOV     P2, #55H
        MOV     A, P2
        MOV     P1, A
        ACALL   DELAY

        ;----- P3 (Port 3, Address 0B0H) -----
        MOV     A, P3
        MOV     P1, A
        ACALL   DELAY

        ;----- ACC (Address 0E0H) -----
        MOV     A, #0C3H
        MOV     P1, A           ; Display ACC value
        ACALL   DELAY

        ;----- B Register (Address 0F0H) -----
        MOV     B, #0A5H
        MOV     A, B
        MOV     P1, A           ; Display B value
        ACALL   DELAY

        ;----- PSW (Address 0D0H) -----
        MOV     A, PSW
        MOV     P1, A           ; Display PSW
        ACALL   DELAY

        ;----- SP (Stack Pointer, Address 81H) -----
        MOV     A, SP
        MOV     P1, A           ; Display SP (default=07H)
        ACALL   DELAY

        ;----- DPH (Address 83H) -----
        MOV     DPTR, #1234H
        MOV     A, DPH
        MOV     P1, A           ; Display DPH = 12H
        ACALL   DELAY

        ;----- DPL (Address 82H) -----
        MOV     A, DPL
        MOV     P1, A           ; Display DPL = 34H
        ACALL   DELAY

        ;----- TMOD (Address 89H) -----
        MOV     TMOD, #01H     ; Set Timer 0 Mode 1
        MOV     A, TMOD
        MOV     P1, A           ; Display TMOD = 01H
        ACALL   DELAY

        ;----- TCON (Address 88H) -----
        MOV     A, TCON
        MOV     P1, A
        ACALL   DELAY

        ;----- TH0 / TL0 (Timer 0) -----
        MOV     TH0, #0FFH
        MOV     TL0, #00H
        MOV     A, TH0
        MOV     P1, A           ; Display TH0 = FFH
        ACALL   DELAY
        MOV     A, TL0
        MOV     P1, A           ; Display TL0 = 00H
        ACALL   DELAY

        ;----- SCON (Serial Control, Address 98H) -----
        MOV     A, SCON
        MOV     P1, A
        ACALL   DELAY

        ;----- IE (Interrupt Enable, Address 0A8H) -----
        MOV     A, IE
        MOV     P1, A
        ACALL   DELAY

        ;----- IP (Interrupt Priority, Address 0B8H) -----
        MOV     A, IP
        MOV     P1, A

DONE:   SJMP    $

DELAY:
        MOV     R6, #150
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
