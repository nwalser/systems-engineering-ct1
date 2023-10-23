;* ------------------------------------------------------------------
;* --  _____       ______  _____                                    -
;* -- |_   _|     |  ____|/ ____|                                   -
;* --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
;* --   | | | '_ \|  __|  \___ \   Zurich University of             -
;* --  _| |_| | | | |____ ____) |  Applied Sciences                 -
;* -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
;* ------------------------------------------------------------------
;* --
;* -- Project     : CT1 - Lab 7
;* -- Description : Control structures
;* -- 
;* -- $Id: main.s 3748 2016-10-31 13:26:44Z kesr $
;* ------------------------------------------------------------------


; -------------------------------------------------------------------
; -- Constants
; -------------------------------------------------------------------
    
                AREA myCode, CODE, READONLY
                    
                THUMB

ADDR_LED_15_0           EQU     0x60000100
ADDR_LED_31_16          EQU     0x60000102
ADDR_7_SEG_BIN_DS1_0    EQU     0x60000114
ADDR_DIP_SWITCH_15_0    EQU     0x60000200
ADDR_HEX_SWITCH         EQU     0x60000211

MASK_HEX_SWITCH 		EQU 	0xF

NR_CASES                EQU     0xB


jump_table
				DCD case_dark
				DCD case_add
				DCD case_sub		
				DCD case_mult
				DCD case_and
				DCD case_or
				DCD case_xor
				DCD case_not
				DCD case_nand
				DCD case_nor
				DCD case_xnor

; -------------------------------------------------------------------
; -- Main
; -------------------------------------------------------------------   
                        
main            PROC
                EXPORT main
                
read_dipsw      
				LDR R7, =ADDR_DIP_SWITCH_15_0
				
				LDRB R0, [R7, #1]
				LDRB R1, [R7, #0]
                    
				LDR R7, =ADDR_LED_15_0

				STRB R0, [R7, #1]
				STRB R1, [R7, #0]
					
					
read_hexsw
				LDR R7, =ADDR_HEX_SWITCH
				LDR R6, =MASK_HEX_SWITCH
				LDR R5, =ADDR_7_SEG_BIN_DS1_0

				LDRB R2, [R7]
				ANDS R2, R2, R6
				STR R2, [R5]
				
				
; switch cases
case_switch
				CMP R2, #NR_CASES
				BHS case_bright
				LSLS R2, #2
				LDR R7, =jump_table
				LDR R7, [R7, R2]
				BX R7
case_dark       
                LDR  R0, =0
                B    display_result  
case_add        
                ADDS R0, R0, R1
                B    display_result
case_sub		
				SUBS R0, R0, R1
				B    display_result
case_mult
				MULS R0, R1, R0
				B    display_result
case_and
				ANDS R0, R0, R1
				B    display_result
case_or
				ORRS R0, R0, R1
				B    display_result
case_xor
				EORS R0, R0, R1
				B    display_result
case_not
				MVNS R0, R0
				B    display_result
case_nand
				ANDS R0, R0, R1
				MVNS R0, R0
				B    display_result
case_nor
				ORRS R0, R0, R1
				MVNS R0, R0
				B    display_result
case_xnor
				EORS R0, R0, R1
				MVNS R0, R0
				B    display_result
case_bright
				LDR  R0, =0xFFFF
                B    display_result

display_result  
				LDR R7, =ADDR_LED_31_16
				STRH R0, [R7]
; switch cases end


                B    read_dipsw
                
                ALIGN
                ENDP

; -------------------------------------------------------------------
; -- End of file
; -------------------------------------------------------------------                      
                END

