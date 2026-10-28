; Exercise 5: Control LED and Motor using Bit-Addressable RAM
; Uses bit-addressable SFR addresses for direct bit manipulation
; LED on P1.0 (bit address 90H), Motor on P1.7 (bit address 97H)

        ORG     0000H

MAIN:
        ; ----- Turn ON LED -----
        SETB    90H             ; P1.0 = 1  (LED ON)

        ACALL   DELAY

        ; ----- Turn OFF LED -----
        CLR     90H             ; P1.0 = 0  (LED OFF)

        ; ----- Turn ON Motor -----
        SETB    97H             ; P1.7 = 1  (Motor ON)

        ACALL   DELAY

        ; ----- Turn OFF Motor -----
        CLR     97H             ; P1.7 = 0  (Motor OFF)

        ; ----- Pattern on P1 using bit addresses -----
        ; Toggle P1.0-P1.3 (LEDs), P1.4-P1.7 (motors/relays)
        MOV     A, #0FH         ; 0000 1111b
        MOV     P1, A           ; Lower nibble ON

        ACALL   DELAY

        MOV     A, #F0H         ; 1111 0000b
        MOV     P1, A           ; Upper nibble ON

        ACALL   DELAY

        MOV     A, #55H         ; 0101 0101b
        MOV     P1, A           ; Alternating pattern

        ACALL   DELAY

        CLR     P1              ; All OFF

DONE:   SJMP    $

;---------- Delay ----------
DELAY:
        MOV     R6, #200
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
