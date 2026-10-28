; Activity 2: Read switches and display on LEDs
; Switches on P0, LEDs on P1

        ORG     0000H

        MOV     P0, #0FFH       ; P0 as input

LOOP:
        MOV     A, P0           ; Read switches
        MOV     P1, A           ; Display on LEDs
        SJMP    LOOP

        END
