#include "Config.oh"

void Console_Ink (unsigned char color) __z88dk_fastcall;
void Console_WriteCh (unsigned char ch) __z88dk_fastcall; // Uses standard font 8x8
void Console_WriteStr (unsigned char *str) __z88dk_fastcall;

extern unsigned char Console_x, Console_y, Console_atr;
/*================================== Header ==================================*/

unsigned char Console_x, Console_y;

void Console_WriteCh (unsigned char ch) __z88dk_fastcall {
  __asm
    ADD  HL,HL
    LD   H,#15
    ADD  HL,HL
    ADD  HL,HL   ; A char font address
    EX   DE,HL
    LD   HL,(_Console_y)
    LD   H,#Config_ScreenTable
    LD   A,#8
DrawLine$:
    EX   AF,AF
    LD   A,(_Console_x)
    ADD  (HL)
    LD   C,A
    INC  H
    LD   B,(HL)
    DEC  H
    LD   A,(DE)  ; Character addr
    LD   (BC),A  ; Screen addr
    INC  B
    LD   (BC),A  ; Screen addr
    INC  DE
    INC  L
    INC  L
    EX   AF,AF
    DEC  A
    JR   NZ,DrawLine$
    LD   A,B     ; Calculate attribute address
    RRCA
    RRCA
    RRCA
    AND  #3
    OR   #0x58
    LD   B,A
    .DB  0x3E    ; LD   A, #0x47
.globl _Console_atr
_Console_atr:
    .DB  0x47
    LD   (BC),A
    LD   HL,#-32
    ADD  HL,BC
    LD   (HL),A  ; Set color to attributes
    LD   HL,#_Console_x
    INC  (HL)    ; Console_x++
  __endasm;
} //Console_WriteCh

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteStr (unsigned char *str) __naked __z88dk_fastcall {
  __asm
NextCh$:
    LD   A,(HL)
    OR   A
    RET  Z
    PUSH HL
    LD   L,A
    CALL _Console_WriteCh
    POP  HL
    INC  HL
    JR   NextCh$
  __endasm;
} //Console_WriteStr

/*--------------------------------- Cut here ---------------------------------*/
void Console_Clear (void) __naked {
  __asm
    LD   A, (_Console_atr)
    LD   (0x5C8D), A ; ATTR_P
    RRCA
    RRCA
    RRCA
    CALL 0x229B
    JP   0xD6B
  __endasm;
} //Console_Clear
