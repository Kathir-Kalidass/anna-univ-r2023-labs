; Exercise 3: Running LED Pattern
; LED moves from P1.0 to P1.7 then restarts
; Uses carry bit rotation for single-bit movement

        ORG     0000H

MAIN:
        MOV     A, #01H        ; Start with P1.0 = 1 (00000001b)

LOOP:
        MOV     P1, A          ; Display current LED pattern
        ACALL  DELAY           ; Wait for visible delay
        RL      A              ; Rotate left: move LED one position
        SJMP    LOOP           ; Continue running pattern

;---------- Visible Delay (~0.5s) ----------
DELAY:
        MOV     R6, #200
D3:     MOV     R7, #250
D2:     MOV     R5, #10
D1:     NOP
        DJNZ    R5, D1
        DJNZ    R7, D2
        DJNZ    R6, D3
        RET

        END
