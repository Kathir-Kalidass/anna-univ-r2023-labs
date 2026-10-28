; Exercise 1: Calculator using Subroutines
; Program repeatedly checks a control variable (choice)
; Choice=1: ADD, Choice=2: SUB, Choice=3: MUL, Choice=4: DIV, Choice=5: EXIT
; Two operands stored in R0 and R1, result displayed on P1

        ORG     0000H

MAIN:
        MOV     R0, #25        ; First operand
        MOV     R1, #10        ; Second operand
        MOV     R2, #03        ; Choice (change this to select operation)

        CJNE    R2, #01, CHK2
        ACALL   ADDITION
        SJMP    DISPLAY

CHK2:   CJNE    R2, #02, CHK3
        ACALL   SUBTRACTION
        SJMP    DISPLAY

CHK3:   CJNE    R2, #03, CHK4
        ACALL   MULTIPLY
        SJMP    DISPLAY

CHK4:   CJNE    R2, #04, CHK5
        ACALL   DIVISION
        SJMP    DISPLAY

CHK5:   CJNE    R2, #05, MAIN
        SJMP    DONE

DISPLAY:
        MOV     P1, A           ; Display result on Port 1
        SJMP    DONE

;---------- Subroutine: Addition ----------
ADDITION:
        MOV     A, R0
        ADD     A, R1
        RET

;---------- Subroutine: Subtraction ----------
SUBTRACTION:
        MOV     A, R0
        CLR     C
        SUBB    A, R1
        RET

;---------- Subroutine: Multiplication ----------
MULTIPLY:
        MOV     A, R0
        MOV     B, R1
        MUL     AB
        RET

;---------- Subroutine: Division ----------
DIVISION:
        MOV     A, R0
        MOV     B, R1
        DIV     AB
        RET

DONE:   SJMP    $

        END
