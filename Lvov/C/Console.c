#include "Config.oh"

void Console_Ink (unsigned char color) __z88dk_fastcall;
void Console_WriteCh (unsigned char ch) __z88dk_fastcall; // Uses standard font 8x8
void Console_WriteStr (unsigned char *str) __z88dk_fastcall;

extern unsigned char Console_x, Console_y, Console_atr;
/*================================== Header ==================================*/

unsigned char Console_x, Console_y;

void Console_WriteCh (unsigned char ch) __z88dk_fastcall {
#asm
#endasm
} //Console_WriteCh

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteStr (unsigned char *str) __naked __z88dk_fastcall {
#asm
NextCh:
    LD   A,(HL)
    OR   A
    RET  Z
    PUSH HL
    LD   L,A
    CALL _Console_WriteCh
    POP  HL
    INC  HL
    JR   NextCh
#endasm
} //Console_WriteStr

/*--------------------------------- Cut here ---------------------------------*/
void Console_Clear (void) __naked {
#asm
#endasm
} //Console_Clear
