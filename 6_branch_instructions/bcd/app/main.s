; ------------------------------------------------------------------
; --  _____       ______  _____                                    -
; -- |_   _|     |  ____|/ ____|                                   -
; --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
; --   | | | '_ \|  __|  \___ \   Zurich University of             -
; --  _| |_| | | | |____ ____) |  Applied Sciences                 -
; -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
; ------------------------------------------------------------------
; --
; -- main.s
; --
; -- CT1 P06 "ALU und Sprungbefehle" mit MUL
; --
; -- $Id: main.s 4857 2019-09-10 17:30:17Z akdi $
; ------------------------------------------------------------------
;Directives
        PRESERVE8
        THUMB

; ------------------------------------------------------------------
; -- Address Defines
; ------------------------------------------------------------------

ADDR_LED_15_0           EQU     0x60000100
ADDR_LED_31_16          EQU     0x60000102
ADDR_DIP_SWITCH_7_0     EQU     0x60000200
ADDR_DIP_SWITCH_15_8    EQU     0x60000201
ADDR_7_SEG_BIN_DS3_0    EQU     0x60000114
ADDR_BUTTONS            EQU     0x60000210

ADDR_LCD_RED            EQU     0x60000340
ADDR_LCD_GREEN          EQU     0x60000342
ADDR_LCD_BLUE           EQU     0x60000344
LCD_BACKLIGHT_FULL      EQU     0xffff
LCD_BACKLIGHT_OFF       EQU     0x0000

; ------------------------------------------------------------------
; -- myCode
; ------------------------------------------------------------------
        AREA myCode, CODE, READONLY

        ENTRY

main    PROC
        export main
            
; STUDENTS: To be programmed
		; load values
		LDR R0, =ADDR_DIP_SWITCH_7_0
		LDRB R1, [R0]
		LDR R0, =ADDR_DIP_SWITCH_15_8
		LDRB R2, [R0]
		
		; display combined
		MOVS R3, R2
		LSLS R3, #4
		ADDS R3, R3, R1
		
		LDR R0, =ADDR_LED_15_0
		STRB R3, [R0]
		
		LDR R0, =ADDR_7_SEG_BIN_DS3_0
		STRB R3, [R0, #0]
		
		; decide with without muls
		LDR R0, =ADDR_BUTTONS
		LDR R0, [R0]
		LSLS R0, #31
		LSRS R0, #31

		CMP R0, #0
		BEQ with_muls

		LDR     R7, =ADDR_LCD_RED
        LDR     R6, =LCD_BACKLIGHT_FULL
        STRH    R6, [R7]
		LDR     R7, =ADDR_LCD_BLUE
        LDR     R6, =LCD_BACKLIGHT_OFF
        STRH    R6, [R7]
			
		; multiplication by 10
		MOVS R3, R2
		LSLS R3, #3 ; multiply by 8
		ADDS R3, R2, R3
		ADDS R2, R2, R3

		B finished_muls

with_muls
		LDR     R7, =ADDR_LCD_BLUE
        LDR     R6, =LCD_BACKLIGHT_FULL
        STRH    R6, [R7]
		LDR     R7, =ADDR_LCD_RED
        LDR     R6, =LCD_BACKLIGHT_OFF
        STRH    R6, [R7]

		; multiplication by 10
		MOVS R3, #10
		MULS R2, R3, R2
		
		B finished_muls		

finished_muls
		ADDS R3, R1, R2
		
		LDR R0, =ADDR_LED_15_0
		STRB R3, [R0, #1]

		LDR R0, =ADDR_7_SEG_BIN_DS3_0
		STRB R3, [R0, #1]

		B main
		

		
; END: To be programmed

        B       main
        ENDP
            
;----------------------------------------------------
; Subroutines
;----------------------------------------------------

;----------------------------------------------------
; pause for disco_lights
pause           PROC
        PUSH    {R0, R1}
        LDR     R1, =1
        LDR     R0, =0x000FFFFF
        
loop        
        SUBS    R0, R0, R1
        BCS     loop
    
        POP     {R0, R1}
        BX      LR
        ALIGN
        ENDP

; ------------------------------------------------------------------
; End of code
; ------------------------------------------------------------------
        END
