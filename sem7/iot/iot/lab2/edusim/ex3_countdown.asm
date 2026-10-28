; Exercise 3: Countdown from 10 to 0 with 1-second delay
; Displays countdown on P1; delay uses nested loops (~1s at 11.0592MHz)

        ORG     0000H

MAIN:
        MOV     R3, #10         ; Start counter at 10

LOOP:
        MOV     P1, R3          ; Display current count on Port 1
        ACALL   DELAY_1SEC      ; Wait ~1 second
        DJNZ    R3, LOOP        ; Decrement and repeat until 0

        MOV     P1, #00H        ; Display 0
DONE:   SJMP    $

;---------- 1-Second Delay Subroutine ----------
; For 11.0592 MHz crystal: ~1 machine cycle = 1.085 us
; Nested loop gives approximately 1 second
DELAY_1SEC:
        MOV     R6, #250
D3:     MOV     R7, #250
D2:     MOV     R4, #18
D1:     NOP
        NOP
        DJNZ    R4, D1
        DJNZ    R7, D2
        DJNZ    R6, D3
        RET

        END
