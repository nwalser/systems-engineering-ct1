# Important:
Under "Options for Target" -> "Asm" -> "Language/Code Generation" you have to select "armasm", otherwise it wont spit out the .lsm file.

# Task 1
MOVS R1, #0xfe
001 00  001 11111110
    opc Rdn imm8

MOVS R2, #MY_CONST
001 00  010 00010010
    opc Rdn imm8 

MOV R11, R2
010001 10  1  0010 011
       opc DN Rm   Rd

LDR R0, [R7]
011 0 1 00000 111 000
    B L imm5  Rn  Rt

STR R3, [R7,R6] 
0101 000 110 111 011
     opc Rm  Rn  Rt

# Task 2
AREA MyAsmVar, DATA, READWRITE
section to define writable variables

AREA MyAsmConst, DATA, READONLY
section to define readonly / constant variables

AREA MyCode, CODE, READONLY
section for code definition

# Task 3
AREA MyAsmVar, DATA, READWRITE
0x10 bytes

AREA MyAsmConst, DATA, READONLY
0x14 bytes

AREA MyCode, CODE, READONLY
0x48 bytes