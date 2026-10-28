; Activity 3: Bit-Addressable Registers
; Access and modify specific bits in bit-addressable RAM locations
; Internal RAM 20H-2FH are bit-addressable (128 bits: 00H-7FH)
; Also demonstrate bit-addressable SFRs (P0, P1, TCON, etc.)

        ORG     0000H

;===== Bit-Addressable RAM (20H-2FH) =====
BIT_RAM:
        ; Byte at 20H = 00H, all bits 0 initially
        ; Bit addresses: 20H.0=00H, 20H.1=01H ... 20H.7=07H
        ;                21H.0=08H, 21H.1=09H ... 2FH.7=7FH

        SETB    00H             ; Set bit 0 of 20H -> 20H = 01H
        SETB    07H             ; Set bit 7 of 20H -> 20H = 81H
        SETB    08H             ; Set bit 0 of 21H -> 21H = 01H
        SETB    0FH             ; Set bit 7 of 21H -> 21H = 81H
        SETB    10H             ; Set bit 0 of 22H -> 22H = 01H

        ; Read bit values
        MOV     C, 00H          ; C = bit 0 of 20H = 1
        MOV     C, 07H          ; C = bit 7 of 20H = 1
        MOV     C, 10H          ; C = bit 0 of 22H = 1

        ; Clear specific bits
        CLR     07H             ; Clear bit 7 of 20H -> 20H = 01H
        CLR     00H             ; Clear bit 0 of 20H -> 20H = 00H

        ; Complement (toggle) a bit
        CPL     08H             ; Toggle bit 0 of 21H: 01H -> 00H
        CPL     08H             ; Toggle back: 00H -> 01H

        ; Display byte values on ports
        MOV     P1, 20H         ; P1 = content of 20H
        MOV     P2, 21H         ; P2 = content of 21H

;===== Bit-Addressable SFRs =====
BIT_SFR:
        ; P1 is bit-addressable: P1.0=90H, P1.1=91H ... P1.7=97H
        SETB    90H             ; P1.0 = 1
        SETB    93H             ; P1.3 = 1
        CLR     90H             ; P1.0 = 0

        ; TCON bits
        SETB    88H             ; IT0 = 1 (TCON.0)
        SETB    8DH             ; TF1 = 1 (TCON.5)

        ; Direct bit test
        JB      93H, BIT_IS_SET ; Jump if P1.3 is set
        SJMP    DONE

BIT_IS_SET:
        MOV     P1, #0FH        ; Display pattern

DONE:   SJMP    $

        END
