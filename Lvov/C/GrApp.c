/* Ver 1.0.0 for ZX Spectrum 48/128 */
/* Use ZXDev to compile this module */

#include "Timer.oh"
#include "Config.oh"

void GrApp_Close (void);
void GrApp_Cls (void);
void GrApp_ScrollDown (unsigned char lines) __z88dk_fastcall;
void GrApp_ScrollUp (unsigned char lines) __z88dk_fastcall;
void GrApp_SetPalette (void);
void GrApp__init (void);

extern unsigned char GrApp_ink, GrApp_paper;
/*================================== Header ==================================*/

static void MoveLineCtoL (void /* A=from; L=to */) __naked {
#asm
        RET
#endasm
} //MoveLineCtoL

/*--------------------------------- Cut here ---------------------------------*/
static void ClearLineL (void /*register L*/) __naked {
#asm
        RET
#endasm
} //ClearLineN

/*--------------------------------- Cut here ---------------------------------*/
void GrApp_ScrollUp (unsigned char lines) __naked __z88dk_fastcall {
/*
  unsigned media, line;
  if (lines > 0) {
    media = 192 - lines;
    for (line = 0; line < media; line ++)
      lmove (line, line + lines);
    while (line < 192)
      lclr (line ++);
  }
*/
// http://pc01.lviv.ua/forum/viewtopic.php?f=3&t=147&hilit=River&start=30#p1649
#asm
        LXI  H, 0
        DAD  SP
        SHLD STACK+1
        LXI  H, 0x4180    ; Src
        SPHL
        LXI  H, 0x4000    ; Dest
        XRA  A
        OUT  0xC2         ; Video RAM on
CYCLE:  POP  D            ; 00
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 01
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 02
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 03
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 04
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 05
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 06
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 07
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 08
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 09
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 0A
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 0B
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 0C
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 0D
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 0E
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 0F
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 10
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 11
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 12
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 13
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 14
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 15
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 16
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 17
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 18
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 19
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 1A
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 1B
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 1C
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 1D
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 1E
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        POP  D            ; 1F
        MOV  M, E
        INX  H
        MOV  M, D
        INX  H
        MOV  A, H
        CPI  0x7E
        JNZ  CYCLE
        MVI  A, 2
        OUT  0xC2
STACK:  LXI  SP, 0
        RET
#endasm
} //GrApp_ScrollUp

/*--------------------------------- Cut here ---------------------------------*/
void GrApp_ScrollDown (unsigned char lines) __naked __z88dk_fastcall {
/*
  for (line = 191; line >= lines; line --)
    lmove (line, line - lines);
  while (line < 192)
    lclr (line --);
*/
#asm // Thanx to Zelya
        LXI  H, 0
        DAD  SP
        SHLD STACK2+1
        LXI  H, 0x8000    ; Dest
        SPHL
        LXI  H, 0x7E80-65 ; Src
        XRA  A
        OUT  0xC2         ; Video RAM on
CYCLE2: MOV  D, M         ; 00
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 01
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 02
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 03
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 04
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 05
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 06
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 07
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 08
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 09
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 0A
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 0B
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 0C
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 0D
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 0E
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 0F
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 10
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 11
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 12
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 13
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 14
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 15
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 16
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 17
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 18
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 19
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 1A
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 1B
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 1C
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 1D
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 1E
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  D, M         ; 1F
        DCX  H
        MOV  E, M
        DCX  H
        PUSH D
        MOV  A, H
        CPI  0x3F
        JNZ  CYCLE2
        MVI  A, 2
        OUT  0C2h
STACK2: LXI  SP, 0
        RET
#endasm
} //GrApp_ScrollDown

/*--------------------------------- Cut here ---------------------------------*/
unsigned char GrApp_ink, GrApp_paper;

void GrApp_SetPalette (void) __naked {
#asm
        RET
#endasm
} //GrApp_SetPalette

/*--------------------------------- Cut here ---------------------------------*/
void GrApp_Cls (void) __naked {
#asm
        XRA  A
        OUT  0xC2         ; Video RAM on
        MVI  A, 15      ; FILL COLOR
        STA  0xBE38
        CALL 0xEBBC       ; FILL
        MVI  A, 2
        OUT  0xC2         ; Video RAM off
        RET
#endasm
} //GrApp_Cls

/*--------------------------------- Cut here ---------------------------------*/
void GrApp__init (void) __naked {
#asm
        MVI  A, 69+128    ; high bit for sound on
        OUT  0xC1         ; PALETTE
        XRA  A
        STA  0xBE38       ; BORDER
        DCR  A
        STA  0xBE3C       ; CURSOR
; Set screen table for fast tiles drawing
        LXI  D, Config_ScreenTable
        LXI  H, 0x4500
        LXI  B, 0x40      ; (next screen line)
SET_TABLE:
        MOV  A, L
        STAX D            ; low byte => Table0
        INR  D
        MOV  A, H
        STAX D            ; high byte => Table1
        DCR  D
        DAD  B            ; to next screen line
        INR  E
        JNZ  SET_TABLE
        JMP  _GrApp_Cls
#endasm
} //GrApp__init

/*--------------------------------- Cut here ---------------------------------*/
void GrApp_Close (void) __naked {
#asm
        JMP  _GrApp_Close
#endasm
} //GrApp__Close
