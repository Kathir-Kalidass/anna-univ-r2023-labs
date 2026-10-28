; Activity 5: Modifying PSW Register
; PSW bits: CY AC F0 RS1 RS0 OV -- P
; RS1:RS0 select register bank (00=Bank0, 01=Bank1, 10=Bank2, 11=Bank3)
; Demonstrates modifying each field and observing effects

        ORG     0000H

;===== Default PSW after reset =====
; PSW = 00H, Bank 0 active, CY=0, AC=0, OV=0, P=0
        MOV     A, PSW          ; A = 00H
        MOV     P1, A           ; Display default PSW

;===== Modify CY (Carry Flag) =====
SET_CY:
        SETB    C               ; CY = 1
        MOV     A, PSW
        MOV     P1, A           ; PSW bit 7 = 1 -> P1 = 80H
        ACALL   DELAY

        CLR     C               ; CY = 0
        MOV     A, PSW
        MOV     P1, A           ; P1 = 00H
        ACALL   DELAY

;===== Modify AC (Auxiliary Carry) =====
SET_AC:
        MOV     A, PSW
        ORL     A, #40H         ; Set AC (bit 6)
        MOV     PSW, A          ; PSW = 40H
        MOV     P1, A           ; P1 = 40H
        ACALL   DELAY

;===== Modify F0 (User Flag) =====
SET_F0:
        MOV     A, PSW
        ORL     A, #20H         ; Set F0 (bit 5)
        MOV     PSW, A          ; PSW = 60H
        MOV     P1, A           ; P1 = 60H
        ACALL   DELAY

;===== Switch Register Banks via RS1:RS0 =====
; Bank 0: RS1=0,RS0=0 -> PSW bits 4:3 = 00
BANK0:
        ANL     PSW, #0E7H      ; Clear RS1,RS0 -> Bank 0
        MOV     R0, #11H        ; Bank 0, R0 = 11H
        MOV     A, PSW
        MOV     P1, A           ; P1 = 00H (Bank 0)
        ACALL   DELAY

; Bank 1: RS1=0,RS0=1 -> PSW bits 4:3 = 01
BANK1:
        ORL     PSW, #08H       ; Set RS0 -> Bank 1
        MOV     R0, #22H        ; Bank 1, R0 = 22H
        MOV     A, PSW
        MOV     P1, A           ; P1 = 08H (Bank 1)
        ACALL   DELAY

; Bank 2: RS1=1,RS0=0 -> PSW bits 4:3 = 10
BANK2:
        ANL     PSW, #0E7H
        ORL     PSW, #10H       ; Set RS1 -> Bank 2
        MOV     R0, #33H        ; Bank 2, R0 = 33H
        MOV     A, PSW
        MOV     P1, A           ; P1 = 10H (Bank 2)
        ACALL   DELAY

; Bank 3: RS1=1,RS0=1 -> PSW bits 4:3 = 11
BANK3:
        ORL     PSW, #18H       ; Set RS1,RS0 -> Bank 3
        MOV     R0, #44H        ; Bank 3, R0 = 44H
        MOV     A, PSW
        MOV     P1, A           ; P1 = 18H (Bank 3)
        ACALL   DELAY

;===== Modify OV (Overflow Flag) via MUL =====
SET_OV:
        ANL     PSW, #0E7H      ; Bank 0
        MOV     A, #80H         ; 10000000 = -128 signed
        MOV     B, #02H
        MUL     AB              ; 80H * 02H = 0100H, OV=1
        MOV     A, PSW
        MOV     P1, A           ; PSW shows OV set if applicable
        ACALL   DELAY

;===== Reset all PSW =====
RESET:
        MOV     PSW, #00H       ; Clear everything
        MOV     A, PSW
        MOV     P1, A           ; P1 = 00H

DONE:   SJMP    $

DELAY:
        MOV     R6, #200
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
