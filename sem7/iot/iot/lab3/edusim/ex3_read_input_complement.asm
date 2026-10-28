; Activity 3: Read 8-bit input, display complement
; Input from P0, complemented output on P1

        ORG     0000H

        MOV     P0, #0FFH       ; P0 as input

LOOP:
        MOV     A, P0           ; Read input
        CPL     A               ; Complement
        MOV     P1, A           ; Display complement on LEDs
        SJMP    LOOP

        END
