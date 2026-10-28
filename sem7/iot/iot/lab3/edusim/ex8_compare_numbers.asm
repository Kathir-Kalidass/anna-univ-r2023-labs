; Activity 8: Compare two 8-bit numbers using 3 LEDs
; LED1 (P1.0) ON: Num1 > Num2
; LED2 (P1.1) ON: Num2 > Num1
; LED3 (P1.2) ON: Equal

        ORG     0000H

MAIN:
        MOV     R0, #30H        ; Number 1
        MOV     R1, #30H        ; Number 2
        MOV     P1, #00H        ; Clear LEDs

        MOV     A, R0
        CLR     C
        SUBB    A, R1           ; A = Num1 - Num2

        JZ      EQUAL
        JC      NUM2_GREATER

;---------- Num1 > Num2 ----------
        SETB    P1.0            ; LED1 ON
        SJMP    DONE

;---------- Num2 > Num1 ----------
NUM2_GREATER:
        SETB    P1.1            ; LED2 ON
        SJMP    DONE

;---------- Equal ----------
EQUAL:
        SETB    P1.2            ; LED3 ON

DONE:   SJMP    $

        END
