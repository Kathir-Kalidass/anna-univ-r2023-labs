; Activity 2: 16-bit ALU Operations
; Demonstrates ADD, SUB, ANL, ORL, XRL on 16-bit numbers
; Shows difference: no 16-bit single instruction, must use carry/borrow chaining

        ORG     0000H

;===== 16-bit ADDITION =====
; Num1=1234H + Num2=0F0F = 2143H
ADD16:
        ; Low byte addition
        MOV     A, #34H         ; Num1 low
        ADD     A, #0FH         ; + Num2 low
        MOV     R0, A           ; R0 = result low = 43H
        ; High byte addition with carry
        MOV     A, #12H         ; Num1 high
        ADDC    A, #0FH         ; + Num2 high + CY
        MOV     R1, A           ; R1 = result high = 21H
        ; R1:R0 = 2143H
        MOV     P1, R0          ; Display low byte
        MOV     P2, R1          ; Display high byte
        ACALL   DELAY

;===== 16-bit SUBTRACTION =====
; Num1=5678H - Num2=1234H = 4444H
SUB16:
        MOV     A, #78H         ; Num1 low
        CLR     C
        SUBB    A, #34H         ; - Num2 low
        MOV     R0, A           ; R0 = 44H
        MOV     A, #56H         ; Num1 high
        SUBB    A, #12H         ; - Num2 high - borrow
        MOV     R1, A           ; R1 = 44H
        ; R1:R0 = 4444H
        MOV     P1, R0
        MOV     P2, R1
        ACALL   DELAY

;===== 16-bit AND =====
; Num1=C5A3H AND Num2=6D5FH = 4503H
AND16:
        ; Low bytes
        MOV     A, #0A3H
        ANL     A, #5FH         ; A = 03H
        MOV     R0, A
        ; High bytes
        MOV     A, #0C5H
        ANL     A, #6DH         ; A = 45H
        MOV     R1, A
        MOV     P1, R0
        MOV     P2, R1
        ACALL   DELAY

;===== 16-bit OR =====
OR16:
        MOV     A, #0A3H
        ORL     A, #5FH         ; A = FFH
        MOV     R0, A
        MOV     A, #0C5H
        ORL     A, #6DH         ; A = EDH
        MOV     R1, A
        MOV     P1, R0
        MOV     P2, R1
        ACALL   DELAY

;===== 16-bit XOR =====
XOR16:
        MOV     A, #0A3H
        XRL     A, #5FH         ; A = FCH
        MOV     R0, A
        MOV     A, #0C5H
        XRL     A, #6DH         ; A = A8H
        MOV     R1, A
        MOV     P1, R0
        MOV     P2, R1

DONE:   SJMP    $

DELAY:
        MOV     R6, #200
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
