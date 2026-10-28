; Activity 10: Check specific bit set or clear
; Byte in R0, bit number in R1 (0-7)
; If bit is SET -> P1.0 ON, If bit is CLEAR -> P1.7 ON

        ORG     0000H

MAIN:
        MOV     R0, #0A5H       ; Byte to check (10100101b)
        MOV     R1, #03H        ; Bit number to check (bit 3)
        MOV     P1, #00H

        MOV     A, R0
        MOV     R2, R1          ; Copy bit number

; Rotate right until desired bit is in carry
CHECK_BIT:
        RRC     A               ; Rotate LSB into carry
        DJNZ    R2, CHECK_BIT   ; Repeat until target bit position
        ; Now carry = target bit value

        JC      BIT_SET
        SJMP    BIT_CLR

BIT_SET:
        SETB    P1.0            ; LED ON = bit is SET
        SJMP    DONE

BIT_CLR:
        SETB    P1.7            ; LED ON = bit is CLEAR

DONE:   SJMP    $

        END
