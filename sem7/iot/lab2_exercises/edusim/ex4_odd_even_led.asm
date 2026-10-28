; Exercise 4: Odd/Even Check with LED
; Number in Accumulator. LSB=0 -> Even -> LED P1.0 ON
;                           LSB=1 -> Odd  -> LED P1.7 ON
; Only one LED ON at a time

        ORG     0000H

MAIN:
        MOV     A, #36H        ; Load 8-bit number (36H = 00110110b = EVEN)
        ; Change to odd number like #37H to test

        CLR     P1             ; Clear all LEDs first

        JB      ACC.0, ODD    ; If LSB=1, number is odd

;---------- Even ----------
EVEN:
        SETB    P1.0           ; Turn ON LED at P1.0
        SJMP    DONE

;---------- Odd ----------
ODD:
        SETB    P1.7           ; Turn ON LED at P1.7

DONE:   SJMP    $

        END
