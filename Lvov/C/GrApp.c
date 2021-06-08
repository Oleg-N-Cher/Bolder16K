/* Ver 1.0.0 for ZX Spectrum 48/128 */
/* Use ZXDev to compile this module */

#include "Timer.oh"
//#include "Config.oh"

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
// http://pc01.lviv.ua/forum/viewtopic.php?f=3&t=147&hilit=River&start=30#p1649

	MVI	A, 0
	OUT	0C2h

AGAIN:	LXI	H, 4040h
	SPHL
	LXI	H, 4000h

CYCLE:
	POP	D	; 00
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 01
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 02
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 03
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 04
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 05
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 06
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 07
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 08
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 09
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 0A
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 0B
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 0C
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 0D
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 0E
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 0F
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 10
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 11
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 12
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 13
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 14
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 15
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 16
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 17
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 18
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 19
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 1A
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 1B
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 1C
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 1D
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 1E
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H
	POP	D	; 1F
	MOV	M, E
	INX	H
	MOV	M, D
	INX	H

	MOV	A, H
	ORA	A
	JP	CYCLE
;	CPI	7Eh
;	JNZ	CYCLE


	JMP	AGAIN

	MVI	A, 2
	OUT	0C2h
	POP	PSW
	POP	B
	POP	D
	POP	H
	RET

END:
	END


*/
#asm
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
#asm
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
        RET
#endasm
} //GrApp_Cls

/*--------------------------------- Cut here ---------------------------------*/
void GrApp__init (void) __naked {
#asm
        MVI  A, 0x48
        OUT  0xC1         ; PALETTE
        XRA  A
        STA  0xBE38       ; BORDER
        DCR  A
        STA  0xBE3C       ; CURSOR
        JMP  0xF836       ; CLS
#endasm
} //GrApp__init

/*--------------------------------- Cut here ---------------------------------*/
void GrApp_Close (void) __naked {
#asm
        JMP  _GrApp_Close
#endasm
} //GrApp__Close
