; Exercise 2: Toggle LED Using Switch
; Switch on P0.0 (input), LED on P1.0 (output)
; Each press of switch toggles LED state
; Uses edge detection to avoid repeated toggling

        ORG     0000H

        CLR     P1.0            ; LED initially OFF

MAIN:
        JB      P0.0, MAIN     ; Wait while switch is HIGH (not pressed)

; Switch pressed (P0.0 = 0) - wait for release
WAIT_REL:
        JNB     P0.0, WAIT_REL ; Wait until switch is released

        CPL     P1.0            ; Toggle LED state
        SJMP    MAIN            ; Go back and wait for next press

        END
