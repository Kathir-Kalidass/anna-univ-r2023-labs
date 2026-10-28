; Exercise 1: Continuously Monitor Switches & Update LEDs
; Switches on P0 (input), LEDs on P1 (output)
; Each switch bit mirrors directly to corresponding LED bit

        ORG     0000H

MAIN:
        MOV     P0, #0FFH       ; Configure P0 as input (all 1s)

LOOP:
        MOV     A, P0           ; Read all switch states from P0
        MOV     P1, A           ; Mirror switch states to LEDs on P1
        SJMP    LOOP            ; Continuously monitor and update

        END
