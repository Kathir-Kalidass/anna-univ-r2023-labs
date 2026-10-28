; Activity 4: Stack Operations - PUSH and POP
; Demonstrates stack pointer behavior and data storage
; SP starts at 07H (default after reset), grows upward

        ORG     0000H

;===== PUSH Operations =====
PUSH_OP:
        ; SP = 07H after reset (Bank 0 ends at 07H)
        MOV     SP, #2FH        ; Set SP to 2FH (above bit-addressable area)

        MOV     A, #55H
        PUSH    ACC             ; SP=30H, (30H)=55H

        MOV     A, #0AAH
        PUSH    ACC             ; SP=31H, (31H)=AAH

        MOV     A, #33H
        PUSH    ACC             ; SP=32H, (32H)=33H

        ; SP is now 32H

        ; Display SP value
        MOV     P2, SP          ; P2 = 32H

;===== POP Operations =====
POP_OP:
        POP     ACC             ; ACC = 33H, SP = 31H
        MOV     P1, A           ; P1 = 33H (last pushed)
        ACALL   DELAY

        POP     ACC             ; ACC = AAH, SP = 30H
        MOV     P1, A           ; P1 = AAH (middle value)
        ACALL   DELAY

        POP     ACC             ; ACC = 55H, SP = 2FH
        MOV     P1, A           ; P1 = 55H (first pushed)
        ACALL   DELAY

        ; SP is back to 2FH
        MOV     P2, SP          ; P2 = 2FH

;===== Nested PUSH/POP with subroutine =====
NESTED:
        MOV     SP, #2FH
        MOV     R0, #42H

        PUSH    00H             ; Save R0 on stack
        ; Modify R0
        MOV     R0, #99H

        ACALL   SUBROUTINE      ; Subroutine uses stack

        POP     00H             ; Restore R0 = 42H
        MOV     P1, R0          ; P1 = 42H

DONE:   SJMP    $

SUBROUTINE:
        MOV     A, R0           ; A = 99H
        INC     A               ; A = 9AH
        MOV     P1, A           ; Display intermediate
        RET

DELAY:
        MOV     R6, #100
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
