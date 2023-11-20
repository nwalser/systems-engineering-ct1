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
; -- CT1 P08 "Strukturierte Codierung" mit Assembler
; --
; -- $Id: struct_code.s 3787 2016-11-17 09:41:48Z kesr $
; ------------------------------------------------------------------
;Directives
        PRESERVE8
        THUMB

; ------------------------------------------------------------------
; -- Address-Defines
; ------------------------------------------------------------------
; input
ADDR_DIP_SWITCH_7_0       EQU        0x60000200
ADDR_BUTTONS              EQU        0x60000210

; output
ADDR_LED_31_0             EQU        0x60000100
ADDR_7_SEG_BIN_DS3_0      EQU        0x60000114
ADDR_LCD_COLOUR           EQU        0x60000340
ADDR_LCD_ASCII            EQU        0x60000300
ADDR_LCD_ASCII_BIT_POS    EQU        0x60000302
ADDR_LCD_ASCII_2ND_LINE   EQU        0x60000330

LCD_COLOR_ON 			  EQU 	     0xFFFF
LCD_COLOR_OFF			  EQU 	     0x0000

LCD_R_OFFSET			  EQU 	     0x0
LCD_G_OFFSET			  EQU 	     0x2
LCD_B_OFFSET			  EQU 	     0x4

; ------------------------------------------------------------------
; -- Program-Defines
; ------------------------------------------------------------------
; value for clearing lcd
ASCII_DIGIT_CLEAR        EQU         0x00000000
LCD_LAST_OFFSET          EQU         0x00000028

; offset for showing the digit in the lcd
ASCII_DIGIT_OFFSET        EQU        0x00000030

; lcd background colors to be written
DISPLAY_COLOUR_RED        EQU        0
DISPLAY_COLOUR_GREEN      EQU        2
DISPLAY_COLOUR_BLUE       EQU        4

; ------------------------------------------------------------------
; -- myConstants
; ------------------------------------------------------------------
        AREA myConstants, DATA, READONLY
; display defines for hex / dec
DISPLAY_BIT               DCB        "Bit "
DISPLAY_2_BIT             DCB        "2"
DISPLAY_4_BIT             DCB        "4"
DISPLAY_8_BIT             DCB        "8"
        ALIGN

; ------------------------------------------------------------------
; -- myCode
; ------------------------------------------------------------------
        AREA myCode, CODE, READONLY
        ENTRY

        ; imports for calls
        import adc_init
        import adc_get_value

main    PROC
        export main
        ; 8 bit resolution, cont. sampling
        BL         adc_init 
        BL         clear_lcd

main_loop
		BL adc_get_value ; function overwrites other registers, this is the reason why i use it first
		MOVS R2, R0 ; R2: store adc value
		
		LDR R0, =ADDR_BUTTONS
		LDRB R1, [R0]
		MOVS R4, #1
		ANDS R1, R1, R4 ; R1: store T0 value
		
		LDR R0, =ADDR_DIP_SWITCH_7_0
		LDRB R3, [R0]
		SUBS R3, R3, R2 ; R3: store subtracted adc value

		; test for cases
		CMP R1, #1
		BEQ case_green
		
		CMP R3, #0
		BGE case_blue
		
		B case_red
		
		
; ----------------------------------------
case_green
		; change display color
		LDR R0, =ADDR_LCD_COLOUR
		LDR R4, =LCD_COLOR_ON
		STRH R4, [R0, #LCD_G_OFFSET]
		LDR R4, =LCD_COLOR_OFF
		STRH R4, [R0, #LCD_R_OFFSET]
		STRH R4, [R0, #LCD_B_OFFSET]

		; display on seven segment display
		LDR R0, =ADDR_7_SEG_BIN_DS3_0
		STRB R2, [R0]

; create led mask
		LSRS R2, #3 ; divison by 8
		MOVS R3, #1
		MOVS R4, #1
create_led_mask_loop
		CMP R2, #0
		BEQ create_led_mask_loop_end
		
		LSLS R3, #1
		ORRS R3, R3, R4
		SUBS R2, R2, #1 ; decrement counter
		
		B create_led_mask_loop
create_led_mask_loop_end
		LDR R0, =ADDR_LED_31_0
		STR R3, [R0]

        B          main_loop


; ----------------------------------------
case_blue
		; change display color
		LDR R0, =ADDR_LCD_COLOUR
		LDR R4, =LCD_COLOR_ON
		STRH R4, [R0, #LCD_B_OFFSET]
		LDR R4, =LCD_COLOR_OFF
		STRH R4, [R0, #LCD_R_OFFSET]
		STRH R4, [R0, #LCD_G_OFFSET]

		; display on seven segment display
		LDR R0, =ADDR_7_SEG_BIN_DS3_0
		STRB R3, [R0]

		; write ascii
		LDR R0, =ADDR_LCD_ASCII
		
test_2_bit
		CMP R3, #4
		BGE test_4_bit
		
		LDR R4, ="2"
		STRB R4, [R0, #0]
		B test_end
test_4_bit
		CMP R3, #16
		BGE over_4_bit
		
		LDR R4, ="4"
		STRB R4, [R0, #0]
		B test_end
over_4_bit		
		LDR R4, ="8"
		STRB R4, [R0, #0]
		B test_end
test_end
		
		LDR R4, ="B"
		STRB R4, [R0, #2]

		LDR R4, ="i"
		STRB R4, [R0, #3]
		
		LDR R4, ="t"
		STRB R4, [R0, #4]


        B          main_loop


; ----------------------------------------
case_red
		; change display color
		LDR R0, =ADDR_LCD_COLOUR
		LDR R4, =LCD_COLOR_ON
		STRH R4, [R0, #LCD_R_OFFSET]
		LDR R4, =LCD_COLOR_OFF
		STRH R4, [R0, #LCD_G_OFFSET]
		STRH R4, [R0, #LCD_B_OFFSET]

		; display on seven segment display
		LDR R0, =ADDR_7_SEG_BIN_DS3_0
		STRB R3, [R0]

; count zeros in diff
		MVNS R3, R3 ; invert R3 to count zeros
		MOVS R4, #0 ; value with number of zeros
		MOVS R5, #0
count_zeros_loop
		CMP R3, #0
		BEQ count_zeros_loop_end
		
		LSLS R3, #1
		ADCS R4, R4, R5
		
		B count_zeros_loop
count_zeros_loop_end
		LDR R0, =ADDR_LCD_ASCII_2ND_LINE
		STRB R4, [R0]


        B          main_loop
		
		
clear_lcd
        PUSH       {R0, R1, R2}
        LDR        R2, =0x0
clear_lcd_loop
        LDR        R0, =ADDR_LCD_ASCII
        ADDS       R0, R0, R2                       ; add index to lcd offset
        LDR        R1, =ASCII_DIGIT_CLEAR
        STR        R1, [R0]
        ADDS       R2, R2, #4                       ; increas index by 4 (word step)
        CMP        R2, #LCD_LAST_OFFSET             ; until index reached last lcd point
        BMI        clear_lcd_loop
        POP        {R0, R1, R2}
        BX         LR

write_bit_ascii
        PUSH       {R0, R1}
        LDR        R0, =ADDR_LCD_ASCII_BIT_POS 
        LDR        R1, =DISPLAY_BIT
        LDR        R1, [R1]
        STR        R1, [R0]
        POP        {R0, R1}
        BX         LR

        ENDP
        ALIGN


; ------------------------------------------------------------------
; End of code
; ------------------------------------------------------------------
        END
