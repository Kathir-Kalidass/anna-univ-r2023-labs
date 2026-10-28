; Exercise 7: Switch Between Register Banks Using PSW
; Demonstrates switching between Register Bank 0, 1, 2, 3
; by modifying RS1 and RS0 bits of PSW

        ORG     0000H

;---------- Register Bank 0 (RS1=0, RS0=0) ----------
BANK0:
        ANL     PSW, #0E7H      ; Clear RS1 and RS0 -> Bank 0 (0000-0007H)
        MOV     R0, #0A0H       ; R0 of Bank 0 = A0H
        MOV     R1, #0B0H       ; R1 of Bank 0 = B0H

;---------- Register Bank 1 (RS1=0, RS0=1) ----------
BANK1:
        ORL     PSW, #08H       ; Set RS0=1 -> Bank 1 (0008-000FH)
        MOV     R0, #10H        ; R0 of Bank 1 = 10H
        MOV     R1, #20H        ; R1 of Bank 1 = 20H

;---------- Register Bank 2 (RS1=1, RS0=0) ----------
BANK2:
        ANL     PSW, #0E7H      ; Clear RS1,RS0
        ORL     PSW, #10H       ; Set RS1=1 -> Bank 2 (0010-0017H)
        MOV     R0, #30H        ; R0 of Bank 2 = 30H
        MOV     R1, #40H        ; R1 of Bank 2 = 40H

;---------- Register Bank 3 (RS1=1, RS0=1) ----------
BANK3:
        ORL     PSW, #18H       ; Set RS1=1,RS0=1 -> Bank 3 (0018-001FH)
        MOV     R0, #50H        ; R0 of Bank 3 = 50H
        MOV     R1, #60H        ; R1 of Bank 3 = 60H

;---------- Verify: Switch back to Bank 0 and read ----------
VERIFY:
        ANL     PSW, #0E7H      ; Switch back to Bank 0
        ; R0 should still be A0H, R1 should still be B0H
        MOV     P1, R0          ; Display R0 of Bank 0 on P1

        ORL     PSW, #08H       ; Switch to Bank 1
        ; R0 should be 10H
        MOV     P2, R0          ; Display R0 of Bank 1 on P2

DONE:   SJMP    $

        END
