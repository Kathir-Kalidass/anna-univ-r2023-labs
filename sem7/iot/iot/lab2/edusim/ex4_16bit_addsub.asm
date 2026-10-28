; Exercise 4: 16-bit Addition / Subtraction of Two Numbers
; Number1 = 0x1234, Number2 = 0x0F0F
; Result stored in R2:R1 (high byte : low byte)

        ORG     0000H

;---------- 16-bit Addition ----------
ADD_MODE:
        ; Number1 = 1234H (R3:R0 = high:low)
        MOV     R3, #12H        ; Number1 high byte
        MOV     R0, #34H        ; Number1 low byte
        ; Number2 = 0F0FH (R5:R4 = high:low)
        MOV     R5, #0FH        ; Number2 high byte
        MOV     R4, #0FH        ; Number2 low byte

        MOV     A, R0
        ADD     A, R4           ; Add low bytes
        MOV     R1, A           ; Store result low byte

        MOV     A, R3
        ADDC    A, R5           ; Add high bytes with carry
        MOV     R2, A           ; Store result high byte

        ; R2:R1 now holds the 16-bit sum
        ; Send to P1 (low byte) and P2 (high byte)
        MOV     P1, R1
        MOV     P2, R2

;---------- 16-bit Subtraction ----------
SUB_MODE:
        ; Number1 = 1234H
        MOV     R3, #12H
        MOV     R0, #34H
        ; Number2 = 0F0FH
        MOV     R5, #0FH
        MOV     R4, #0FH

        CLR     C               ; Clear borrow
        MOV     A, R0
        SUBB    A, R4           ; Subtract low bytes
        MOV     R1, A           ; Store result low byte

        MOV     A, R3
        SUBB    A, R5           ; Subtract high bytes with borrow
        MOV     R2, A           ; Store result high byte

        ; R2:R1 now holds the 16-bit difference
        MOV     P1, R1
        MOV     P2, R2

DONE:   SJMP    $

        END
