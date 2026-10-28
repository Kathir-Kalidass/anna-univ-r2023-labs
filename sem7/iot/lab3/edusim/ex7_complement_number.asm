; Activity 7: Complement 8-bit number and display
; Number in R0, complement displayed on P1

        ORG     0000H

MAIN:
        MOV     R0, #55H        ; Input number (01010101b)
        MOV     A, R0
        CPL     A               ; Complement: A9H (10101001b)
        MOV     P1, A           ; Display on LEDs

        ; Also demonstrate with another number
        MOV     R0, #0FH
        MOV     A, R0
        CPL     A               ; F0H
        MOV     P1, A

        SJMP    $

        END
