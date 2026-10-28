; Exercise 5: 8-bit Arithmetic with Overflow/Carry LEDs
; ADD: Carry LED=P1.7, SUB: Borrow LED=P1.6
; MUL overflow: P1.5, DIV by zero: P1.4
; Results in Register Banks: Bank0=ADD, Bank1=SUB, Bank2=MUL, Bank3=DIV

        ORG     0000H

START:
        MOV     R0, #200       ; Number A
        MOV     R1, #100       ; Number B
        MOV     P1, #00H       ; Clear all LEDs

;===== ADDITION (Result in Bank 0) =====
        ANL     PSW, #0E7H     ; Select Bank 0 (RS1=0,RS0=0)
        MOV     A, R0
        ADD     A, R1          ; A = A + B
        JC      ADD_CARRY      ; If carry, set overflow LED
        SJMP    SUBTRACTION
ADD_CARRY:
        SETB    P1.7           ; Carry LED ON

;===== SUBTRACTION (Result in Bank 1) =====
SUBTRACTION:
        ORL     PSW, #08H      ; Select Bank 1 (RS1=0,RS0=1)
        MOV     A, R0
        CLR     C
        SUBB    A, R1          ; A = A - B
        JC      SUB_BORROW     ; If borrow, set borrow LED
        SJMP    MULTIPLY
SUB_BORROW:
        SETB    P1.6           ; Borrow LED ON

;===== MULTIPLICATION (Result in Bank 2) =====
MULTIPLY:
        ANL     PSW, #0E7H
        ORL     PSW, #10H      ; Select Bank 2 (RS1=1,RS0=0)
        MOV     A, R0
        MOV     B, R1
        MUL     AB              ; A = low byte, B = high byte
        JNZ     MUL_OVERFLOW   ; If B != 0, overflow occurred
        SJMP    DIVISION
MUL_OVERFLOW:
        SETB    P1.5           ; MUL overflow LED ON

;===== DIVISION (Result in Bank 3) =====
DIVISION:
        ORL     PSW, #18H      ; Select Bank 3 (RS1=1,RS0=1)
        MOV     A, R0
        MOV     B, R1
        CJNE    B, #0, DO_DIV  ; Check divide by zero
        SETB    P1.4           ; Division by zero LED ON
        SJMP    DONE
DO_DIV:
        DIV     AB              ; A = quotient, B = remainder

DONE:   SJMP    $

        END
