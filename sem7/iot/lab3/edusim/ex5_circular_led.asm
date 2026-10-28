; Activity 5: Circular LED pattern using rotate instructions
; Single bit circles through P1.0 -> P1.7 and back to P1.0
; Alternates direction: left then right

        ORG     0000H

MAIN:
        MOV     A, #01H         ; Start at P1.0

;----- Move left: P1.0 to P1.7 -----
LEFT:
        MOV     P1, A
        ACALL   DELAY
        RL      A
        CJNE    A, #80H, LEFT  ; Continue until P1.7

;----- Move right: P1.7 to P1.0 -----
RIGHT:
        MOV     P1, A
        ACALL   DELAY
        RR      A
        CJNE    A, #01H, RIGHT ; Continue until P1.0

        SJMP    MAIN           ; Repeat cycle

DELAY:
        MOV     R6, #150
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
