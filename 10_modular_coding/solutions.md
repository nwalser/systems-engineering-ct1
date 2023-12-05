# Aufgabe 1.2
## a
- Step into nicht möglich 
- read8() verwendet intern den Register 1 um Daten zwischen zu speichern
## b
- Step into möglich auf level von assembler code
## c
- Step into mit c source möglich

## Grund
Dem Debugger sind mit jedem Schritt zusätzliche Informationen zur verfügung gestanden, die zum ausführen eines Programmes nicht benötigt werden, jedoch zum Debuggen angefügt werden können.



# Aufgabe 1.3
## fromelf.exe
fromelf.exe befindet sich abweichen der Dokumentation am Ort: C:\Keil_v5\ARM\ARMCLANG\bin\fromelf.exe

## Symbole
Lokale Symbole: Lc
Importierte Symbole: Gb
Exportierte Symbole: Gb  Ref

## Einträge die nicht im Header File Stehen
Das können Symbole sein die zum Beispiel vom Compiler generiert wurden/benötigt werden.

## Selber Header Files Generiere
Ja es fehlen verschiedene dinge. 
- Eines ist zum Beispiel die Interpretation der Daten auf Library Seite. (uint_8, int_8)?

# Aufgabe 1.4
Alle möglichen Informationen sind angewählt.

Interessante Sektionen im Linker Map File:
- Global Symbols
- Memory Map of the image


## generated files
### toggle.o

** ELF Header Information

    File Name: toggle.o

    Machine class: ELFCLASS32 (32-bit)
    Data encoding: ELFDATA2LSB (Little endian)
    Header version: EV_CURRENT (Current version)
    Operating System ABI: none
    ABI Version: 0
    File Type: ET_REL (Relocatable object) (1)
    Machine: EM_ARM (ARM)

    Entry offset (in SHF_ENTRYSECT section): 0x00000000
    Flags: None (0x05000000)

    ARM ELF revision: 5 (ABI version 2)

    Header size: 52 bytes (0x34)
    Program header entry size: 0 bytes (0x0)
    Section header entry size: 40 bytes (0x28)

    Program header entries: 0
    Section header entries: 20

    Program header offset: 0 (0x00000000)
    Section header offset: 1448 (0x000005a8)

    Section header string table index: 1



** Section #1 '.strtab' (SHT_STRTAB)
    Size   : 246 bytes


** Section #2 '.text' (SHT_PROGBITS) [SHF_ALLOC + SHF_EXECINSTR]
    Size   : 0 bytes (alignment 4)
    Address: 0x00000000


** Section #3 '.text.toggle' (SHT_PROGBITS) [SHF_ALLOC + SHF_EXECINSTR]
    Size   : 28 bytes (alignment 4)
    Address: 0x00000000


** Section #4 '.rel.text.toggle' (SHT_REL) [SHF_INFO_LINK]
    Size   : 32 bytes (alignment 4)
    Symbol table #19 '.symtab'
    4 relocations applied to section #3 '.text.toggle'


** Section #5 '.ARM.exidx.text.toggle' (SHT_ARM_EXIDX) [SHF_ALLOC + SHF_LINK_ORDER]
    Size   : 8 bytes (alignment 4)
    Address: 0x00000000
    Link to section #3 '.text.toggle'


** Section #6 '.rel.ARM.exidx.text.toggle' (SHT_REL) [SHF_INFO_LINK]
    Size   : 8 bytes (alignment 4)
    Symbol table #19 '.symtab'
    1 relocations applied to section #5 '.ARM.exidx.text.toggle'


** Section #7 '.data.value' (SHT_PROGBITS) [SHF_ALLOC + SHF_WRITE]
    Size   : 1 bytes
    Address: 0x00000000


** Section #8 '.debug_abbrev' (SHT_PROGBITS)
    Size   : 80 bytes


** Section #9 '.debug_info' (SHT_PROGBITS)
    Size   : 91 bytes


** Section #10 '.rel.debug_info' (SHT_REL) [SHF_INFO_LINK]
    Size   : 96 bytes (alignment 4)
    Symbol table #19 '.symtab'
    12 relocations applied to section #9 '.debug_info'


** Section #11 '.debug_str' (SHT_PROGBITS) [SHF_MERGE + SHF_STRINGS]
    Size   : 214 bytes


** Section #12 '.comment' (SHT_PROGBITS) [SHF_MERGE + SHF_STRINGS]
    Size   : 69 bytes


** Section #13 '.note.GNU-stack' (SHT_PROGBITS)
    Size   : 0 bytes


** Section #14 '.ARM.attributes' (SHT_ARM_ATTRIBUTES)
    Size   : 80 bytes


** Section #15 '.debug_frame' (SHT_PROGBITS)
    Size   : 44 bytes (alignment 4)


** Section #16 '.rel.debug_frame' (SHT_REL) [SHF_INFO_LINK]
    Size   : 16 bytes (alignment 4)
    Symbol table #19 '.symtab'
    2 relocations applied to section #15 '.debug_frame'


** Section #17 '.debug_line' (SHT_PROGBITS)
    Size   : 131 bytes


** Section #18 '.rel.debug_line' (SHT_REL) [SHF_INFO_LINK]
    Size   : 8 bytes (alignment 4)
    Symbol table #19 '.symtab'
    1 relocations applied to section #17 '.debug_line'


** Section #19 '.symtab' (SHT_SYMTAB)
    Size   : 240 bytes (alignment 4)
    String table #1 '.strtab'
    Last local symbol no. 12

    Symbol table .symtab (14 symbols, 12 local)

      #  Symbol Name                Value      Bind  Sec  Type  Vis  Size
    ========================================================================

      1  toggle.c                   0x00000000   Lc  Abs  File  De
      2  [Anonymous Symbol]         0x00000000   Lc    3  Sect  De
      3  $t.0                       0x00000000   Lc    3   --   De
      4  __arm_cp.0_0               0x00000014   Lc    3   --   De   0x4
      5  __arm_cp.0_1               0x00000018   Lc    3   --   De   0x4
      6  $d.1                       0x00000014   Lc    3   --   De
      7  value                      0x00000000   Lc    7  Data  De   0x1
      8  [Anonymous Symbol]         0x00000000   Lc    7  Sect  De
      9  [Anonymous Symbol]         0x00000000   Lc    8  Sect  De
     10  [Anonymous Symbol]         0x00000000   Lc   11  Sect  De
     11  [Anonymous Symbol]         0x00000000   Lc   15  Sect  De
     12  [Anonymous Symbol]         0x00000000   Lc   17  Sect  De
     13  toggle                     0x00000001   Gb    3  Code  Hi   0x14
     14  write8                     0x00000000   Gb  Ref   --   De

### main.o

** ELF Header Information

    File Name: main.o

    Machine class: ELFCLASS32 (32-bit)
    Data encoding: ELFDATA2LSB (Little endian)
    Header version: EV_CURRENT (Current version)
    Operating System ABI: Linux
    ABI Version: 0
    File Type: ET_REL (Relocatable object) (1)
    Machine: EM_ARM (ARM)

    Entry offset (in SHF_ENTRYSECT section): 0x00000000
    Flags: None (0x05000000)

    ARM ELF revision: 5 (ABI version 2)

    Header size: 52 bytes (0x34)
    Program header entry size: 0 bytes (0x0)
    Section header entry size: 40 bytes (0x28)

    Program header entries: 0
    Section header entries: 21

    Program header offset: 0 (0x00000000)
    Section header offset: 1732 (0x000006c4)

    Section header string table index: 1


** Section #1 '.strtab' (SHT_STRTAB)
    Size   : 279 bytes


** Section #2 '.text' (SHT_PROGBITS) [SHF_ALLOC + SHF_EXECINSTR]
    Size   : 0 bytes (alignment 4)
    Address: 0x00000000


** Section #3 '.text.main' (SHT_PROGBITS) [SHF_ALLOC + SHF_EXECINSTR]
    Size   : 64 bytes (alignment 4)
    Address: 0x00000000


** Section #4 '.rel.text.main' (SHT_REL) [SHF_INFO_LINK]
    Size   : 40 bytes (alignment 4)
    Symbol table #20 '.symtab'
    5 relocations applied to section #3 '.text.main'


** Section #5 '.ARM.exidx.text.main' (SHT_ARM_EXIDX) [SHF_ALLOC + SHF_LINK_ORDER]
    Size   : 8 bytes (alignment 4)
    Address: 0x00000000
    Link to section #3 '.text.main'


** Section #6 '.rel.ARM.exidx.text.main' (SHT_REL) [SHF_INFO_LINK]
    Size   : 8 bytes (alignment 4)
    Symbol table #20 '.symtab'
    1 relocations applied to section #5 '.ARM.exidx.text.main'


** Section #7 '.bss.last' (SHT_NOBITS) [SHF_ALLOC + SHF_WRITE]
    Size   : 1 bytes
    Address: 0x00000000


** Section #8 '.ARM.use_no_argv' (SHT_PROGBITS) [SHF_ALLOC + SHF_WRITE + 0x00200000]
    Size   : 4 bytes (alignment 4)
    Address: 0x00000000


** Section #9 '.debug_abbrev' (SHT_PROGBITS)
    Size   : 104 bytes


** Section #10 '.debug_info' (SHT_PROGBITS)
    Size   : 141 bytes


** Section #11 '.rel.debug_info' (SHT_REL) [SHF_INFO_LINK]
    Size   : 128 bytes (alignment 4)
    Symbol table #20 '.symtab'
    16 relocations applied to section #10 '.debug_info'


** Section #12 '.debug_str' (SHT_PROGBITS) [SHF_MERGE + SHF_STRINGS]
    Size   : 232 bytes


** Section #13 '.comment' (SHT_PROGBITS) [SHF_MERGE + SHF_STRINGS]
    Size   : 69 bytes


** Section #14 '.note.GNU-stack' (SHT_PROGBITS)
    Size   : 0 bytes


** Section #15 '.ARM.attributes' (SHT_ARM_ATTRIBUTES)
    Size   : 80 bytes


** Section #16 '.debug_frame' (SHT_PROGBITS)
    Size   : 48 bytes (alignment 4)


** Section #17 '.rel.debug_frame' (SHT_REL) [SHF_INFO_LINK]
    Size   : 16 bytes (alignment 4)
    Symbol table #20 '.symtab'
    2 relocations applied to section #16 '.debug_frame'


** Section #18 '.debug_line' (SHT_PROGBITS)
    Size   : 173 bytes


** Section #19 '.rel.debug_line' (SHT_REL) [SHF_INFO_LINK]
    Size   : 8 bytes (alignment 4)
    Symbol table #20 '.symtab'
    1 relocations applied to section #18 '.debug_line'


** Section #20 '.symtab' (SHT_SYMTAB)
    Size   : 272 bytes (alignment 4)
    String table #1 '.strtab'
    Last local symbol no. 12

    Symbol table .symtab (16 symbols, 12 local)

      #  Symbol Name                Value      Bind  Sec  Type  Vis  Size
    ========================================================================

      1  main.c                     0x00000000   Lc  Abs  File  De
      2  [Anonymous Symbol]         0x00000000   Lc    3  Sect  De
      3  $t.0                       0x00000000   Lc    3   --   De
      4  __arm_cp.0_0               0x00000038   Lc    3   --   De   0x4
      5  __arm_cp.0_1               0x0000003c   Lc    3   --   De   0x4
      6  $d.1                       0x00000038   Lc    3   --   De
      7  last                       0x00000000   Lc    7  Data  De   0x1
      8  [Anonymous Symbol]         0x00000000   Lc    7  Sect  De
      9  [Anonymous Symbol]         0x00000000   Lc    9  Sect  De
     10  [Anonymous Symbol]         0x00000000   Lc   12  Sect  De
     11  [Anonymous Symbol]         0x00000000   Lc   16  Sect  De
     12  [Anonymous Symbol]         0x00000000   Lc   18  Sect  De
     13  main                       0x00000001   Gb    3  Code  Hi   0x38
     14  read8                      0x00000000   Gb  Ref   --   De
     15  toggle                     0x00000000   Gb  Ref   --   De
     16  __ARM_use_no_argv          0x00000000   Gb    8  Data  De   0x4

###  ..\lib\read_write.lib

** ELF Header Information

    File Name: ..\lib\read_write.lib
    Module Name: read.o

    Machine class: ELFCLASS32 (32-bit)
    Data encoding: ELFDATA2LSB (Little endian)
    Header version: EV_CURRENT (Current version)
    Operating System ABI: none
    ABI Version: 0
    File Type: ET_REL (Relocatable object) (1)
    Machine: EM_ARM (ARM)

    Entry offset (in SHF_ENTRYSECT section): 0x00000000
    Flags: None (0x05000000)

    ARM ELF revision: 5 (ABI version 2)

    Header size: 52 bytes (0x34)
    Program header entry size: 0 bytes (0x0)
    Section header entry size: 40 bytes (0x28)

    Program header entries: 0
    Section header entries: 10

    Program header offset: 0 (0x00000000)
    Section header offset: 776 (0x00000308)

    Section header string table index: 7



** Section #1 '.text' (SHT_PROGBITS) [SHF_ALLOC + SHF_EXECINSTR]
    Size   : 4 bytes (alignment 2)
    Address: 0x00000000


** Section #2 '.arm_vfe_header' (SHT_PROGBITS)
    Size   : 4 bytes (alignment 4)


** Section #3 '.comment' (SHT_PROGBITS)
    Size   : 158 bytes


** Section #4 '.debug_frame' (SHT_PROGBITS)
    Size   : 60 bytes


** Section #6 '.rel.debug_frame' (SHT_REL)
    Size   : 16 bytes (alignment 4)
    Symbol table #5 '.symtab'
    2 relocations applied to section #4 '.debug_frame'


** Section #5 '.symtab' (SHT_SYMTAB)
    Size   : 128 bytes (alignment 4)
    String table #8 '.strtab'
    Last local symbol no. 5

    Symbol table .symtab (7 symbols, 5 local)

      #  Symbol Name                Value      Bind  Sec  Type  Vis  Size
    ========================================================================

      1  read.c                     0x00000000   Lc  Abs  File  De
      2  $t                         0x00000000   Lc    1   --   De
      3  .text                      0x00000000   Lc    1  Sect  De
      4  BuildAttributes$$THM_ISAv3M$S$PE$A:L22$X:L11$S22$IEEE1$IW$USESV6$~STKCKD$USESV7$~SHL$OSPACE$EBA8$REQ8$PRES8$EABIv2
                                    0x00000000   Lc  Abs   --   De
      5  __ARM_grp_.debug_frame$5   0x00000000   Lc    4  Data  De
      6  read8                      0x00000001   Gb    1  Code  Hi   0x4
      7  Lib$$Request$$armlib       0x00000000   Wk  Ref  Code  Hi


** Section #7 '.shstrtab' (SHT_STRTAB)
    Size   : 91 bytes


** Section #8 '.strtab' (SHT_STRTAB)
    Size   : 184 bytes


** Section #9 '.ARM.attributes' (SHT_ARM_ATTRIBUTES)
    Size   : 68 bytes





** ELF Header Information

    File Name: ..\lib\read_write.lib
    Module Name: write.o

    Machine class: ELFCLASS32 (32-bit)
    Data encoding: ELFDATA2LSB (Little endian)
    Header version: EV_CURRENT (Current version)
    Operating System ABI: none
    ABI Version: 0
    File Type: ET_REL (Relocatable object) (1)
    Machine: EM_ARM (ARM)

    Entry offset (in SHF_ENTRYSECT section): 0x00000000
    Flags: None (0x05000000)

    ARM ELF revision: 5 (ABI version 2)

    Header size: 52 bytes (0x34)
    Program header entry size: 0 bytes (0x0)
    Section header entry size: 40 bytes (0x28)

    Program header entries: 0
    Section header entries: 10

    Program header offset: 0 (0x00000000)
    Section header offset: 780 (0x0000030c)

    Section header string table index: 7



** Section #1 '.text' (SHT_PROGBITS) [SHF_ALLOC + SHF_EXECINSTR]
    Size   : 4 bytes (alignment 2)
    Address: 0x00000000


** Section #2 '.arm_vfe_header' (SHT_PROGBITS)
    Size   : 4 bytes (alignment 4)


** Section #3 '.comment' (SHT_PROGBITS)
    Size   : 160 bytes


** Section #4 '.debug_frame' (SHT_PROGBITS)
    Size   : 60 bytes


** Section #6 '.rel.debug_frame' (SHT_REL)
    Size   : 16 bytes (alignment 4)
    Symbol table #5 '.symtab'
    2 relocations applied to section #4 '.debug_frame'


** Section #5 '.symtab' (SHT_SYMTAB)
    Size   : 128 bytes (alignment 4)
    String table #8 '.strtab'
    Last local symbol no. 5

    Symbol table .symtab (7 symbols, 5 local)

      #  Symbol Name                Value      Bind  Sec  Type  Vis  Size
    ========================================================================

      1  write.c                    0x00000000   Lc  Abs  File  De
      2  $t                         0x00000000   Lc    1   --   De
      3  .text                      0x00000000   Lc    1  Sect  De
      4  BuildAttributes$$THM_ISAv3M$S$PE$A:L22$X:L11$S22$IEEE1$IW$USESV6$~STKCKD$USESV7$~SHL$OSPACE$EBA8$REQ8$PRES8$EABIv2
                                    0x00000000   Lc  Abs   --   De
      5  __ARM_grp_.debug_frame$5   0x00000000   Lc    4  Data  De
      6  write8                     0x00000001   Gb    1  Code  Hi   0x4
      7  Lib$$Request$$armlib       0x00000000   Wk  Ref  Code  Hi


** Section #7 '.shstrtab' (SHT_STRTAB)
    Size   : 91 bytes


** Section #8 '.strtab' (SHT_STRTAB)
    Size   : 186 bytes


** Section #9 '.ARM.attributes' (SHT_ARM_ATTRIBUTES)
    Size   : 68 bytes