; Activity 1: 8-bit Basic ALU Operations
; Demonstrates: ADD, SUB, MUL, DIV, ANL, ORL, XRL, RL, RR, CPL, CLR, SETB
; Each result displayed on P1 for observation

        ORG     0000H

;----- ADD: A = 25H + 1AH = 3FH -----
ADD_OP:
        MOV     A, #25H
        ADD     A, #1AH         ; A = 3FH, CY=0, AC=0
        MOV     P1, A           ; P1 = 3FH
        ACALL   DELAY

;----- SUB: A = 50H - 30H = 20H -----
SUB_OP:
        MOV     A, #50H
        CLR     C
        SUBB    A, #30H         ; A = 20H, CY=0
        MOV     P1, A           ; P1 = 20H
        ACALL   DELAY

;----- MUL: A=05H * B=06H = 001EH -----
MUL_OP:
        MOV     A, #05H
        MOV     B, #06H
        MUL     AB              ; A=1EH(low), B=00H(high)
        MOV     P1, A           ; P1 = 1EH
        ACALL   DELAY

;----- DIV: A=25H / B=06H -----
DIV_OP:
        MOV     A, #25H
        MOV     B, #06H
        DIV     AB              ; A=06H(quotient), B=01H(remainder)
        MOV     P1, A           ; P1 = 06H
        ACALL   DELAY

;----- ANL: A = 0C5H AND 06DH = 45H -----
ANL_OP:
        MOV     A, #0C5H        ; 11000101
        ANL     A, #06DH        ; 01101101 = 01000101 = 45H
        MOV     P1, A           ; P1 = 45H
        ACALL   DELAY

;----- ORL: A = 0C5H OR 06DH = EDH -----
ORL_OP:
        MOV     A, #0C5H        ; 11000101
        ORL     A, #06DH        ; 01101101 = 11101101 = EDH
        MOV     P1, A           ; P1 = EDH
        ACALL   DELAY

;----- XRL: A = 0C5H XOR 06DH = A8H -----
XRL_OP:
        MOV     A, #0C5H        ; 11000101
        XRL     A, #06DH        ; 01101101 = 10101000 = A8H
        MOV     P1, A           ; P1 = A8H
        ACALL   DELAY

;----- RL: Rotate Left -----
RL_OP:
        MOV     A, #01H         ; 00000001
        RL      A               ; 00000010
        RL      A               ; 00000100
        RL      A               ; 00001000
        MOV     P1, A           ; P1 = 08H
        ACALL   DELAY

;----- RR: Rotate Right -----
RR_OP:
        MOV     A, #80H         ; 10000000
        RR      A               ; 01000000
        RR      A               ; 00100000
        RR      A               ; 00010000
        MOV     P1, A           ; P1 = 10H
        ACALL   DELAY

;----- CPL: Complement -----
CPL_OP:
        MOV     A, #55H         ; 01010101
        CPL     A               ; 10101001 = A9H
        MOV     P1, A           ; P1 = A9H
        ACALL   DELAY

;----- CLR: Clear Accumulator -----
CLR_OP:
        MOV     A, #0FFH
        CLR     A               ; A = 00H
        MOV     P1, A           ; P1 = 00H
        ACALL   DELAY

;----- SETB: Set Bit -----
SETB_OP:
        MOV     P1, #00H
        SETB    P1.0            ; P1.0 = 1
        SETB    P1.7            ; P1.7 = 1
        MOV     A, P1           ; A = 81H
        MOV     P1, A           ; P1 = 81H

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
