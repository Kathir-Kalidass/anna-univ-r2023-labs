; Activity 4: Rotate 8-bit data left continuously
; Data rotates left and displayed on P1

        ORG     0000H

MAIN:
        MOV     A, #01H         ; Start: 00000001

LOOP:
        MOV     P1, A           ; Display on LEDs
        ACALL   DELAY           ; Visible delay
        RL      A               ; Rotate left
        SJMP    LOOP

DELAY:
        MOV     R6, #200
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
