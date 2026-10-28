; Exercise 9: Monitor Accumulator Status with LEDs
; ACC == 0:   LED P1.0 ON (zero indicator)
; ACC != 0:   LED P1.1 ON (non-zero indicator)
; ACC.7 == 1: LED P1.2 ON, then clear ACC.7

        ORG     0000H

MAIN:
        MOV     A, #0FFH       ; Load ACC with value (0FFH has bit7=1)
        ; Try values: #00H (zero), #55H (non-zero, bit7=0),
        ;             #FFH (non-zero, bit7=1), #80H (only bit7)

        MOV     P1, #00H       ; Clear all LEDs

        ; ----- Check zero -----
        JNZ     NOT_ZERO
        SETB    P1.0           ; ACC is zero -> LED P1.0 ON
        SJMP    CHECK_BIT7

NOT_ZERO:
        SETB    P1.1           ; ACC is non-zero -> LED P1.1 ON

CHECK_BIT7:
        ; ----- Check and handle bit 7 -----
        JB      ACC.7, BIT7_SET
        SJMP    DONE

BIT7_SET:
        SETB    P1.2           ; Bit 7 is set -> LED P1.2 ON
        CLR     ACC.7          ; Clear bit 7

DONE:   SJMP    $

        END
