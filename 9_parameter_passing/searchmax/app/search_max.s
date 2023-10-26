                AREA myCode, CODE, READONLY
                THUMB
                    
INT_MIN  EQU      0x80000000
	
	
; -------------------------------------------------------------------                    
; Searchmax
; - tableaddress in R0
; - table length in R1
; - result returned in R0
; -------------------------------------------------------------------   
search_max      PROC
                EXPORT search_max
					
				PUSH {R4}
				LDR R4, =INT_MIN
				
test_element
				SUBS R1, #1
				CMP R1, #0
				BLT test_element_end
				
				MOVS R3, R1
				LSLS R3, #2
				ADDS R3, R3, R0
				
				LDR R3, [R3]
				
				CMP R4, R3
				BGT not_larger
				MOVS R4, R3
not_larger
				B test_element
test_element_end
				MOVS R0, R4

				POP {R4}
				BX LR

                ALIGN
                ENDP
; -------------------------------------------------------------------
; -- End of file
; -------------------------------------------------------------------                      
                END

