; Exercise 6: Reverse an Array Using Stack (PUSH/POP)
; Array of 5 elements starting at 30H, reversed in-place using stack

        ORG     0000H

MAIN:
        ; ----- Initialize array at internal RAM 30H-34H -----
        MOV     30H, #11H
        MOV     31H, #22H
        MOV     32H, #33H
        MOV     33H, #44H
        MOV     34H, #55H

        ; Array = [11H, 22H, 33H, 44H, 55H]

        ; ----- Push all elements onto stack -----
        MOV     R0, #30H        ; Pointer to start of array
        MOV     R1, #05H        ; Number of elements

PUSH_LOOP:
        MOV     A, @R0
        PUSH    ACC             ; Push element onto stack
        INC     R0
        DJNZ    R1, PUSH_LOOP

        ; ----- Pop elements back (reversed order) -----
        MOV     R0, #30H        ; Reset pointer to start
        MOV     R1, #05H        ; Number of elements

POP_LOOP:
        POP     ACC             ; Pop from stack (LIFO = reversed)
        MOV     @R0, A          ; Store back to array
        INC     R0
        DJNZ    R1, POP_LOOP

        ; Array is now [55H, 44H, 33H, 22H, 11H]
        ; Display reversed array on P1 (last element)

        MOV     P1, 30H         ; Display first element of reversed array

DONE:   SJMP    $

        END
