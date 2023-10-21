; ------------------------------------------------------------------
; --  _____       ______  _____                                    -
; -- |_   _|     |  ____|/ ____|                                   -
; --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
; --   | | | '_ \|  __|  \___ \   Zurich University of             -
; --  _| |_| | | | |____ ____) |  Applied Sciences                 -
; -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
; ------------------------------------------------------------------
; --
; -- table.s
; --
; -- CT1 P04 Ein- und Ausgabe von Tabellenwerten
; --
; -- $Id: table.s 800 2014-10-06 13:19:25Z ruan $
; ------------------------------------------------------------------
;Directives
        PRESERVE8
        THUMB
; ------------------------------------------------------------------
; -- Symbolic Literals
; ------------------------------------------------------------------
ADDR_DIP_SWITCH_7_0         EQU     0x60000200
ADDR_DIP_SWITCH_15_8        EQU     0x60000201
ADDR_DIP_SWITCH_31_24       EQU     0x60000203
ADDR_LED_7_0                EQU     0x60000100
ADDR_LED_15_8               EQU     0x60000101
ADDR_LED_23_16              EQU     0x60000102
ADDR_LED_31_24              EQU     0x60000103
ADDR_BUTTONS                EQU     0x60000210
ADDR_DS0					EQU 	0x60000114
ADDR_DS2					EQU 	0x60000115

BITMASK_KEY_T0              EQU     0x01
BITMASK_LOWER_NIBBLE        EQU     0x0F

; ------------------------------------------------------------------
; -- Variables
; ------------------------------------------------------------------
        AREA MyAsmVar, DATA, READWRITE
; STUDENTS: To be programmed
store_table             SPACE   32  ; reserve 32 bytes
; END: To be programmed
        ALIGN

; ------------------------------------------------------------------
; -- myCode
; ------------------------------------------------------------------
        AREA myCode, CODE, READONLY

main    PROC
        EXPORT main

readInput
        BL    waitForKey                    ; wait for key to be pressed and released
; STUDENTS: To be programmed

;INPUT section
		; load index
		LDR R7, =ADDR_DIP_SWITCH_15_8
		LDRB R2, [R7] ; read switch 15 to 7 values
		LDR R7, =BITMASK_LOWER_NIBBLE
		ANDS R2, R2, R7 ; mask index input
		
		; load value 15_0
		LDR R7, =ADDR_DIP_SWITCH_7_0
		LDRH R1, [R7] ; read switch 15 to 0 values
		; display value 15_0
		LDR R7, =ADDR_LED_7_0
		STRH R1, [R7]
		; store value
		LDR R7, =store_table
		LSLS R2, R2, #1 ; *2
		STRH R1, [R7, R2] ; store into table with offset
		
; OUTPUT section
		; load index
		LDR R7, =ADDR_DIP_SWITCH_31_24
		LDRB R2, [R7] ; read switch 31 to 24 values
		LDR R7, =BITMASK_LOWER_NIBBLE
		ANDS R2, R2, R7 ; mask index input
		; display index
		LDR R7, =ADDR_LED_31_24
		STRB R2, [R7]
		
		; load value
		LDR R7, =store_table
		LSLS R2, R2, #1 ; *2
		LDRH R1, [R7, R2] ; load from table with offset
		; display value
		LDR R7, =ADDR_LED_23_16
		STRB R1, [R7]
		
		; display on 7 segment displays
		LDR R7, =ADDR_DS0
		STRB R1, [R7]
		
		LDR R7, =ADDR_DS2
		LSRS R1, R1, #8 ; *2
		STRB R1, [R7]
		
; END: To be programmed
        B       readInput
        ALIGN

; ------------------------------------------------------------------
; Subroutines
; ------------------------------------------------------------------

; wait for key to be pressed and released
waitForKey
        PUSH    {R0, R1, R2}
        LDR     R1, =ADDR_BUTTONS           ; laod base address of keys
        LDR     R2, =BITMASK_KEY_T0         ; load key mask T0

waitForPress
        LDRB    R0, [R1]                    ; load key values
        TST     R0, R2                      ; check, if key T0 is pressed
        BEQ     waitForPress

waitForRelease
        LDRB    R0, [R1]                    ; load key values
        TST     R0, R2                      ; check, if key T0 is released
        BNE     waitForRelease
                
        POP     {R0, R1, R2}
        BX      LR
        ALIGN

; ------------------------------------------------------------------
; End of code
; ------------------------------------------------------------------
        ENDP
        END
