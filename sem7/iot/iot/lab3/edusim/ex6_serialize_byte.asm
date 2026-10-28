; Activity 6: Serialize data byte A5H through a single output pin
; Sends each bit of A5H serially through P1.0 (LSB first)
; Bit sequence: 1,0,1,0,0,1,0,1 (A5H = 10100101b)

        ORG     0000H

        MOV     R0, #08H        ; 8 bits to send
        MOV     A, #0A5H        ; Data = 10100101b

SERIAL_LOOP:
        RRC     A               ; Rotate right -> carry = LSB
        MOV     P1.0, C         ; Output bit to P1.0
        ACALL   BIT_DELAY       ; Bit period delay
        DJNZ    R0, SERIAL_LOOP

        ; All 8 bits serialized
        CLR     P1.0            ; Line idle low
        SJMP    $

;---------- Bit period delay (~500us for visible demo) ----------
BIT_DELAY:
        MOV     R6, #05H
BD2:    MOV     R7, #60H
BD1:    NOP
        DJNZ    R7, BD1
        DJNZ    R6, BD2
        RET

        END
