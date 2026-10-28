; Activity 7: Loops, Subroutine Calls, and Jumps
; Demonstrates: AJMP, SJMP, LJMP, DJNZ, JC, JNC, JZ, JNZ,
;               JB, JNB, JBC, CJNE, JMP
;               LCALL, ACALL, RET, RETI

        ORG     0000H

;===== 1. LOOP with DJNZ =====
LOOP_DJNZ:
        MOV     R0, #05H        ; Loop counter = 5
LOOP1:
        MOV     A, R0
        MOV     P1, A           ; Display counter on P1
        ACALL   DELAY
        DJNZ    R0, LOOP1       ; Decrement and loop if not zero
        ; After loop R0=0, P1=0

;===== 2. Conditional Jumps: JZ / JNZ =====
JZ_JNZ:
        MOV     A, #00H
        JZ      ZERO_FOUND      ; A=0, so jump taken
        MOV     P1, #0FFH       ; This is skipped
ZERO_FOUND:
        MOV     P1, #01H        ; P1 = 01H
        ACALL   DELAY

        MOV     A, #55H
        JNZ     NON_ZERO        ; A!=0, jump taken
        MOV     P1, #00H        ; Skipped
NON_ZERO:
        MOV     P1, #02H        ; P1 = 02H
        ACALL   DELAY

;===== 3. Carry Flag Jumps: JC / JNC =====
JC_JNC:
        CLR     C               ; CY = 0
        JNC     NO_CARRY        ; CY=0, jump taken
        SETB    P1.0            ; Skipped
NO_CARRY:
        MOV     P1, #03H
        ACALL   DELAY

        SETB    C               ; CY = 1
        JC      HAS_CARRY      ; CY=1, jump taken
        CLR     P1.0            ; Skipped
HAS_CARRY:
        MOV     P1, #04H
        ACALL   DELAY

;===== 4. Bit Jumps: JB, JNB, JBC =====
BIT_JUMPS:
        SETB    P1.0            ; Set P1.0 = 1
        JB      P1.0, BIT_SET  ; P1.0=1, jump taken
        MOV     P1, #00H
BIT_SET:
        MOV     P1, #05H
        ACALL   DELAY

        CLR     P1.0            ; P1.0 = 0
        JNB     P1.0, BIT_CLR  ; P1.0=0, jump taken
        MOV     P1, #00H
BIT_CLR:
        MOV     P1, #06H
        ACALL   DELAY

        SETB    P1.0
        JBC     P1.0, BIT_CLR_BC ; P1.0=1, jump + clear bit
BIT_CLR_BC:
        MOV     P1, #07H        ; P1.0 was cleared
        ACALL   DELAY

;===== 5. CJNE: Compare and Jump if Not Equal =====
CJNE_OP:
        MOV     R0, #30H
        CJNE    R0, #30H, NOT_EQ1 ; R0 == 30H, no jump
        MOV     P1, #08H        ; Equal case
        SJMP    CJNE_DONE
NOT_EQ1:
        MOV     P1, #09H        ; Not equal case
CJNE_DONE:
        ACALL   DELAY

        ; CJNE with immediate: unsigned comparison
        MOV     A, #20H
        CJNE    A, #30H, NOT_EQ2 ; 20H != 30H, jump
NOT_EQ2:
        JC      A_LESS          ; CY=1 means A < 30H
        MOV     P1, #0AH        ; A >= 30H
        SJMP    CJNE_DONE2
A_LESS:
        MOV     P1, #0BH        ; A < 30H
CJNE_DONE2:
        ACALL   DELAY

;===== 6. SJMP / AJMP / LJMP =====
SJMP_OP:
        SJMP    AJMP_LABEL      ; Short jump (same 2K page)
        ; SJMP can jump -128 to +127 bytes

AJMP_LABEL:
        AJMP    LJMP_LABEL      ; Absolute jump (same 2K page)
        ; AJMP jumps within 2K block

LJMP_LABEL:
        LJMP    INDIRECT_JMP    ; Long jump (anywhere in 64K)

;===== 7. JMP @A+DPTR (Indirect Jump) =====
INDIRECT_JMP:
        MOV     DPTR, #JMP_TABLE
        MOV     A, #02H         ; Select case 2
        RL      A               ; A = 04H (word alignment)
        JMP     @A+DPTR         ; Jump to table entry

JMP_TABLE:
        AJMP    CASE0           ; Entry 0
        AJMP    CASE1           ; Entry 1
        AJMP    CASE2           ; Entry 2
        AJMP    CASE3           ; Entry 3

CASE0:
        MOV     P1, #10H
        SJMP    CALL_DEMO
CASE1:
        MOV     P1, #11H
        SJMP    CALL_DEMO
CASE2:
        MOV     P1, #12H        ; Selected - P1 = 12H
        SJMP    CALL_DEMO
CASE3:
        MOV     P1, #13H

;===== 8. ACALL / LCALL / RET =====
CALL_DEMO:
        ACALL   SUB_LOCAL       ; Auto CALL (within 2K page)
        ACALL   DELAY

        LCALL   SUB_FAR         ; Long CALL (anywhere in 64K)
        ACALL   DELAY

        ; RETI demo (used for interrupts, returns from ISR)
        ; Shown conceptually - RETI restores priority flip-flop

DONE:   SJMP    $

;----- Local Subroutine -----
SUB_LOCAL:
        MOV     A, #0BBH
        MOV     P1, A
        RET                     ; Return to caller

;----- Far Subroutine -----
SUB_FAR:
        MOV     A, #0CCH
        MOV     P1, A
        RET

;----- Delay -----
DELAY:
        MOV     R6, #100
D2:     MOV     R7, #200
D1:     NOP
        DJNZ    R7, D1
        DJNZ    R6, D2
        RET

        END
