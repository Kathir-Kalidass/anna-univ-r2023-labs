; Activity 12: Traffic Light Controller using Timer Delays
; P1.0 = Red, P1.1 = Yellow, P1.2 = Green
; Timer 0 Mode 1 for ~2 second delays

        ORG     0000H
        LJMP    MAIN

;---------- Timer 0 Delay: ~2 seconds ----------
; At 11.0592MHz: Timer overflow at 65536 counts
; 2 sec = 122 overflow cycles (approx)
DELAY_2SEC:
        MOV     R3, #122        ; Overflow counter
D_WAIT:
        MOV     TMOD, #01H      ; Timer 0 Mode 1
        MOV     TH0, #00H       ; Load for full count
        MOV     TL0, #00H
        SETB    TR0             ; Start timer
D_LOOP:
        JNB     TF0, D_LOOP    ; Wait for overflow
        CLR     TR0             ; Stop timer
        CLR     TF0             ; Clear overflow flag
        DJNZ    R3, D_WAIT     ; Repeat 122 times (~2 sec)
        RET

;---------- Main Program ----------
MAIN:
        ;----- RED ON (5 seconds approx) -----
        CLR     P1.1            ; Yellow OFF
        CLR     P1.2            ; Green OFF
        SETB    P1.0            ; Red ON
        ACALL   DELAY_2SEC
        ACALL   DELAY_2SEC     ; ~4 sec, add another for ~6 sec
        ACALL   DELAY_2SEC

        ;----- GREEN ON (5 seconds) -----
        CLR     P1.0            ; Red OFF
        SETB    P1.2            ; Green ON
        ACALL   DELAY_2SEC
        ACALL   DELAY_2SEC
        ACALL   DELAY_2SEC

        ;----- YELLOW ON (2 seconds) -----
        CLR     P1.2            ; Green OFF
        SETB    P1.1            ; Yellow ON
        ACALL   DELAY_2SEC

        ;----- Cycle repeats -----
        CLR     P1.1            ; Yellow OFF
        SJMP    MAIN

        END
