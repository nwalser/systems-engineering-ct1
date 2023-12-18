
                IMPORT init_measurement
                IMPORT clear_IRQ_EXTI0
                IMPORT clear_IRQ_TIM2

; -----------------------------------------------------------------------------
; -- Constants
; -----------------------------------------------------------------------------

                AREA myCode, CODE, READONLY

                THUMB

REG_GPIOA_IDR       EQU  0x40020010
LED_15_0            EQU  0x60000100
LED_16_31           EQU  0x60000102
REG_CT_7SEG         EQU  0x60000114
REG_SETENA0         EQU  0xe000e100


; -----------------------------------------------------------------------------
; -- Main
; -----------------------------------------------------------------------------             
main            PROC
                EXPORT main
					
                BL   init_measurement    

                ; Configure NVIC (enable interrupt channel)

				LDR R0, =REG_SETENA0
				MOVS R1, #0x40 ;lade 0100'0000 also IRQ6 = 1 setzen
				LDR R2, =0x10000000
				ORRS R1, R1, R2 ;lade IRQ28 = 1
				STR R1, [R0]

                ; Initialize variables
                ; STUDENTS: To be programmed	
				MOVS R7, #0x0 ;lade 0 zum R7, der dann die blinkende LEDS übernimmt

                ; END: To be programmed

loop			
				;bonus: lade global high score zum 7seg + 1 Byte (linken zwei anzeigen)
				LDR R1, =glob_h_s
				LDR R2, [R1]
				STRB R2, [R0, #1]

                B    loop

                ENDP

; -----------------------------------------------------------------------------
; Handler for EXTI0 interrupt
; -----------------------------------------------------------------------------

EXTI0_IRQHandler PROC
				EXPORT EXTI0_IRQHandler
					
				;Link Register auf den Stack legen, da er noch beim Sprung nach clear_IRQ überschrieben wird
				PUSH {LR}	
				
				;zaehler laden und +1 zaehlen
				LDR R0, =zaehler
				LDR R1, [R0]
				ADDS R1, #1
				STR R1, [R0]
				
				;interrupt clearen und zurück springen
				BL clear_IRQ_EXTI0
				POP {PC}
				
				ENDP

 
; -----------------------------------------------------------------------------                   
; Handler for TIM2 interrupt
; -----------------------------------------------------------------------------

TIM2_IRQHandler PROC
				EXPORT TIM2_IRQHandler
				PUSH {LR}	
                
				;toggle R7 (variable für die leds)
				MVNS R7, R7
				LDR R0, =LED_16_31
				STRH R7, [R0]
				
				BL clear_IRQ_TIM2
				POP {PC}
				ENDP
				ALIGN

; -----------------------------------------------------------------------------
; -- Variables
; -----------------------------------------------------------------------------

                AREA myVars, DATA, READWRITE

zaehler		DCD		0x0
glob_h_s	DCD		0x0



; -----------------------------------------------------------------------------
; -- End of file
; -----------------------------------------------------------------------------
                END
