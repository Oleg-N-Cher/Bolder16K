#include "Config.oh"

void GrTiles_DrawTile_fastcall (/*unsigned char x, unsigned char y,*/ unsigned char* tile) __z88dk_fastcall;
/*================================== Header ==================================*/

void GrTiles_DrawTile_fastcall (/*unsigned char x, unsigned char y,*/ unsigned char* tile) __naked __z88dk_fastcall {
  __asm          ; HL = tile address
.globl _GrTiles_x
.globl _GrTiles_y
    .DB  0x11    ; LD DE, yx
_GrTiles_x:
    .DB  0       ; E = x
_GrTiles_y:
    .DB  0       ; D = y
    LD   A,D     ; y
    ADD  A
    ADD  D       ; * 6
    ADD  A
    LD   C,A     ; BC = #TAB[y * 6]
    LD   B,#Config_ScreenTable
    LD   A,(BC)
    ADD  E       ; + x
    LD   E,A     ; low screen addr byte
    INC  B
    LD   A,(BC)
    LD   D,A     ; high screen addr byte
; #1
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
; #2
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
    LD   A,D
    AND  #7
    CALL Z,DOWN_DE8$
; #3
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
; #4
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
    LD   A,D
    AND  #7
    CALL Z,DOWN_DE8$
; #5
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
; #6
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
    LD   A,D
    AND  #7
    CALL Z,DOWN_DE8$
; #7
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
; #8
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
    LD   A,D
    AND  #7
    CALL Z,DOWN_DE8$
; #9
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
; #10
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
    LD   A,D
    AND  #7
    CALL Z,DOWN_DE8$
; #11
    LDI
    LD   A,(HL)
    LD   (DE),A
    INC  HL
    DEC  E
    INC  D
; #12
    LDI          ; 16t
    LD   A,(HL)  ; 7t
    LD   (DE),A  ; 7t
    RET
DOWN_DE8$:
    LD   A,E
    ADD  #32
    LD   E,A
    RET  C
    LD   A,D
    SUB  #8
    LD   D,A
    RET
  __endasm;
} //GrTiles_DrawTile_fastcall
