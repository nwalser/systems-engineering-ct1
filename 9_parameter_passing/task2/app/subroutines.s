                AREA myCode, CODE, READONLY
                THUMB
						
; extern void out_word(uint32_t out_address, uint32_t out_value);
out_word      	PROC
                EXPORT out_word
				
				STR R1, [R0]
					
				BX LR
				ENDP	
					
					
; extern uint32_t in_word(uint32_t in_address);
in_word      	PROC
                EXPORT in_word
					
				LDR R0, [R0]
					
				BX LR
				ENDP
					
				ALIGN
				END
					