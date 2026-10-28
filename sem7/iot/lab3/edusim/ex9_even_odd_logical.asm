; Activity 9: Even/Odd using logical operations
; Number in R0. LSB=0 -> Even (P1.0 ON), LSB=1 -> Odd (P1.7 ON)
; Uses ANL to isolate LSB

        ORG     0000H

MAIN:
        MOV     R0, #37H        ; Test number (37H = odd)
        MOV     P1, #00H

        MOV     A, R0
        ANL     A, #01H         ; Isolate LSB using AND
        JNZ     ODD

;---------- Even ----------
        SETB    P1.0            ; LED P1.0 ON
        SJMP    DONE

;---------- Odd ----------
ODD:
        SETB    P1.7            ; LED P1.7 ON

DONE:   SJMP    $

        END
