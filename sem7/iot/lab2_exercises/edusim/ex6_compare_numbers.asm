; Exercise 6: Compare Two 8-bit Numbers
; Num1 > Num2: LED P1.0 ON
; Num2 > Num1: LED P1.1 ON
; Num1 == Num2: LED P1.2 ON

        ORG     0000H

MAIN:
        MOV     R0, #45H       ; Number 1
        MOV     R1, #45H       ; Number 2 (change to test)
        MOV     P1, #00H       ; Clear all LEDs

        MOV     A, R0
        CLR     C
        SUBB    A, R1          ; A = Num1 - Num2

        JZ      EQUAL          ; If result = 0, numbers are equal
        JC      NUM2_GT        ; If carry set, Num2 > Num1

;---------- Num1 > Num2 ----------
NUM1_GT:
        SETB    P1.0           ; LED 1 ON
        SJMP    DONE

;---------- Num2 > Num1 ----------
NUM2_GT:
        SETB    P1.1           ; LED 2 ON
        SJMP    DONE

;---------- Equal ----------
EQUAL:
        SETB    P1.2           ; LED 3 ON

DONE:   SJMP    $

        END
