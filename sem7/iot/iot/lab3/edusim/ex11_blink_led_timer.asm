; Activity 11: Blink LED at 1-second intervals using Timer 0
; LED on P1.0 toggles every ~1 second
; Timer 0 Mode 1 (16-bit), crystal = 11.0592 MHz
; 1 sec = 500ms x 2 (toggle each half)
; Timer count for 500ms: 65536 - 46080 = 19456 = 4C00H

        ORG     0000H
        LJMP    MAIN

        ORG     000BH           ; Timer 0 ISR vector
        LJMP    TIMER0_ISR

;---------- Main Program ----------
MAIN:
        MOV     TMOD, #01H      ; Timer 0, Mode 1 (16-bit)
        MOV     TH0, #4CH       ; Timer high byte
        MOV     TL0, #00H       ; Timer low byte
        MOV     R2, #00H        ; Toggle counter
        SETB    ET0             ; Enable Timer 0 interrupt
        SETB    EA              ; Enable global interrupts
        SETB    TR0             ; Start Timer 0

HERE:   SJMP    HERE            ; Infinite loop, ISR handles toggle

;---------- Timer 0 ISR ----------
TIMER0_ISR:
        CLR     TR0             ; Stop timer
        MOV     TH0, #4CH       ; Reload timer value
        MOV     TL0, #00H
        SETB    TR0             ; Restart timer

        CPL     P1.0            ; Toggle LED
        RETI

        END
