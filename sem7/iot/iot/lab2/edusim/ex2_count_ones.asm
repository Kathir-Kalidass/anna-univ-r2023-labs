; Exercise 2: Count Number of 1s in an 8-bit Number
; Input number in R0, count stored in R2, result displayed on P1

        ORG     0000H

MAIN:
        MOV     R0, #0A5H       ; 8-bit number = 10100101b (should count 5 ones)
        MOV     R2, #00H        ; Counter for 1s = 0
        MOV     A, R0           ; Copy number to A

LOOP:
        JZ      DONE            ; If A == 0, no more bits to check
        RRC     A               ; Rotate right through carry -> carry = LSB
        JNC     SKIP            ; If carry = 0, skip increment
        INC     R2              ; Carry = 1, increment count

SKIP:
        SJMP    LOOP            ; Repeat for next bit

DONE:
        MOV     P1, R2          ; Display count of 1s on Port 1
        SJMP    $

        END
