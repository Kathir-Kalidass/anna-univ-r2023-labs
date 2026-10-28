; Exercise 7: AND, OR, XOR Operations on Two 8-bit Numbers
; Num1 at 30H, Num2 at 31H
; AND result at 40H, OR result at 41H, XOR result at 42H
; Display XOR result on P1 for verification

        ORG     0000H

MAIN:
        ; ----- Store input numbers in memory -----
        MOV     30H, #0C5H     ; Num1 = 11000101b
        MOV     31H, #06DH     ; Num2 = 01101101b

        ; ----- AND Operation -----
        MOV     A, 30H
        ANL     A, 31H         ; A = Num1 AND Num2
        MOV     40H, A         ; Store AND result at 40H

        ; ----- OR Operation -----
        MOV     A, 30H
        ORL     A, 31H         ; A = Num1 OR Num2
        MOV     41H, A         ; Store OR result at 41H

        ; ----- XOR Operation -----
        MOV     A, 30H
        XRL     A, 31H         ; A = Num1 XOR Num2
        MOV     42H, A         ; Store XOR result at 42H

        ; ----- Display results on P1 -----
        MOV     P1, 40H        ; P1 = AND result
        ACALL   DELAY
        MOV     P1, 41H        ; P1 = OR result
        ACALL   DELAY
        MOV     P1, 42H        ; P1 = XOR result

DONE:   SJMP    $

;---------- Delay ----------
DELAY:
        MOV     R6, #200
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
