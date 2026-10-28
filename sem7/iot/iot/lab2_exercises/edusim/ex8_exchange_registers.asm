; Exercise 8: Exchange Two Registers, then INC/DEC
; R0 and R1 are exchanged, then R0 is incremented, R1 is decremented
; Final values displayed on P1 (R0) and P2 (R1)

        ORG     0000H

MAIN:
        MOV     R0, #25        ; R0 = 25
        MOV     R1, #10        ; R1 = 10

        ; ----- Exchange R0 and R1 using ACC -----
        MOV     A, R0          ; A = R0
        MOV     R2, A          ; R2 = R0 (temp)
        MOV     A, R1          ; A = R1
        MOV     R0, A          ; R0 = old R1
        MOV     A, R2          ; A = old R0
        MOV     R1, A          ; R1 = old R0

        ; Now R0 = 10, R1 = 25

        ; ----- Increment R0 -----
        INC     R0             ; R0 = 10 + 1 = 11

        ; ----- Decrement R1 -----
        DEC     R1             ; R1 = 25 - 1 = 24

        ; ----- Display final values -----
        MOV     P1, R0         ; P1 = R0 (11 = 0BH)
        MOV     P2, R1         ; P2 = R1 (24 = 18H)

DONE:   SJMP    $

        END
