; Activity 1: Switch flips alternately display AAH and 55H
; Switch on P0.0, LEDs on P1
; Each switch press toggles between AAH and 55H pattern

        ORG     0000H

        MOV     P1, #55H        ; Initial pattern

MAIN:
        JB      P0.0, MAIN     ; Wait while switch is HIGH

; Switch pressed - debounce
        ACALL   DELAY
        JB      P0.0, MAIN     ; False press, ignore

; Wait for release
WAIT_REL:
        JNB     P0.0, WAIT_REL

; Toggle between AAH and 55H
        MOV     A, P1
        CPL     A               ; Complement: 55H<->AAH
        MOV     P1, A
        SJMP    MAIN

DELAY:
        MOV     R6, #200
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
