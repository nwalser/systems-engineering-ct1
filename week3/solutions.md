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

# Task 5
A1: It depends on the endianess of the processor.
A2: It depends on the architecture of the processor. If it is a 64bit architecture the memory can only be divided into sections of size 4bytes. Therefore if a section can not be used completely it will get padded with zeros.
The actual address is only known after linking

# Task 6
Variable Name   | Content       | Start address
add_dip_switch  | 0x60000200    | 0x0800221c
const_table[0]  | 0x01234567    | 0x08002220
const_table[1]  | 0x12345678    | 0x08002222
const_table[2]  | 0x99996666    | 0x08002224
const_table[3]  | 0x34567890    | 0x08002226

# Task 7
Line    | Instruction                       | Content of target register
A1      | MOVS R1, #0xfe                    | 0xFE
A2      | MOV R11, R2                       | 0x12
A3      | LDR R3, =ADDR_DIP_SWITCH_31_0     | 0x60000200
A4      | LDR R7, addr_dip_switch           | 0x60000200
A5      | LDR R7, =addr_dip_switch          | 0x0800221c
A6      | LDR R1, [R7, #4]                  | 0x12345678
A7      | LDR R3, [R7, R6]                  | 0x34567890

# Task 9
1. Set breakpoint on line 97
2. Set memory at this location to these bytes.
0x2000 0000 67 45 23 01 78 56 34 12 **55 55 55 55**
3. Set breakpoint at line 104
4. Run programm to line 104