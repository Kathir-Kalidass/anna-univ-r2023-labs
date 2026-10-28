; Exercise 8: Read and Display P0, P1, ACC, B, PSW, SP, DPTR
; Reads special function registers and displays their values on ports

        ORG     0000H

MAIN:
        ; ----- Read and Display P0 -----
        MOV     A, P0           ; Read Port 0
        MOV     P1, A           ; Display P0 value on P1

        ; ----- Read and Display P1 -----
        MOV     A, P1           ; Read Port 1
        MOV     P2, A           ; Display P1 value on P2

        ; ----- Read and Display ACC -----
        MOV     A, #55H         ; Load ACC with a known value
        MOV     P1, A           ; Display ACC on P1

        ; ----- Read and Display B Register -----
        MOV     B, #0AAH        ; Load B with known value
        MOV     P2, B           ; Display B on P2

        ; ----- Read and Display PSW -----
        MOV     A, PSW          ; Read Program Status Word
        MOV     P1, A           ; Display PSW on P1

        ; ----- Read and Display SP -----
        MOV     A, SP           ; Read Stack Pointer
        MOV     P2, A           ; Display SP on P2

        ; ----- Read and Display DPTR -----
        MOV     DPTR, #1234H   ; Load DPTR with known value
        MOV     A, DPH          ; Read DPTR High byte
        MOV     P1, A           ; Display DPH on P1
        MOV     A, DPL          ; Read DPTR Low byte
        MOV     P2, A           ; Display DPL on P2

        ; ----- Summary Display Cycle -----
        ; Continuously read and display on P1 and P2
LOOP:
        MOV     A, PSW
        MOV     P1, A           ; P1 = PSW

        MOV     A, SP
        MOV     P2, A           ; P2 = SP

        SJMP    LOOP

        END
