#include "Config.oh"
#include "GrApp.oh"

void Control_ChangePalette (void) __preserves_regs(iyl,iyh);
unsigned char Control_Get (void);
unsigned char Control_PressedAnyKey (void);
unsigned char Control_ReadKey (void);
/*================================== Header ==================================*/

void Control_ChangePalette (void) __preserves_regs(iyl,iyh) {
  __asm
    LD   A,#0xF7
    IN   A,(#0xFE)
    CPL
    AND  #3       ; 00000021
    RET  Z        ; '1' & '2' not pressed
    LD   B,A
    AND  #1       ; '1'
    JR   Z,PAL_KEY2$
PAL_KEY1$:
NEXT_INK$:        ; Change ink
    LD   HL,#_GrApp_ink
    LD   A,(HL)
    INC  A
    AND  #7
    LD   (HL),A
    LD   A,(_GrApp_paper)
    AND  #7
    CP   (HL)     ; Ink must be # Paper
    JR   Z,NEXT_INK$
PAL_KEY2$:
    BIT  1,B      ; '2'
    JR   Z,SET_PALETTE$
NEXT_PAPER$:      ; Change paper
    LD   HL,#_GrApp_paper
    LD   A,(HL)
    INC  A
    AND  #0xF
    LD   (HL),A
    DEC  HL
    AND  #7
    CP   (HL)     ; Ink must be # Paper
    JR   Z,NEXT_PAPER$
SET_PALETTE$:
    CALL _GrApp_SetPalette
    SCF           ; Set flag C if pallette was changed
  __endasm;
} //Control_ChangePalette

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_PressedAnyKey (void) {
  __asm
    CALL  _Control_ChangePalette
    JR    C,RET_FALSE$ ; RETURN FALSE if palette was changed
    CALL  0x28E        ; Scan keys
    INC   DE
    LD    A,E
    OR    D
    LD    L,#1         ; TRUE
    RET   NZ
RET_FALSE$:
    LD    L,#0         ; FALSE
  __endasm;
} //Control_PressedAnyKey

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_ReadKey (void) { // With auto-repeat
__asm
  RES  5,1(IY)
LOOP_REPEAT$:
  BIT  5,1(IY)
  JR   Z,LOOP_REPEAT$
  LD   L,-50(IY)
__endasm;
} //Input_Read_Repeat

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_Get (void) __naked {
__asm
/* �� ������� Deja Vu #09, ��������, 1999
 (C) Rezonance group
 �������� ����� Kempston-��������� */
        CALL _Control_ChangePalette
.globl _Control_GetCustom
_Control_GetCustom:
;����� ����������� Q, A, O, P, E, �����
;������������ Sinclair 1/2 � Kempston. �� ������
;� �������� 'L' � ������� �������� ���������
;�� ����� ��������� ����������� ��������.

KEY1A$: LD    HL,#KEY1F$
        LD    C,#0
        LD    A,(HL)
KEY1B$: INC   HL
        IN    A,(#0xFE)
        AND   (HL)
        INC   HL
        JR    NZ,KEY1C$
        LD    A,(HL)
        OR    C
        LD    C,A
KEY1C$: INC   HL
        LD    A,(HL)
        AND   A
        JR    NZ,KEY1B$
        LD    L,C
.globl __KEMPSTON
__KEMPSTON:
        .DB   0xC9  ; RET or IN
#ifdef __detect_kempston__
        .DB   0x1F
#endif //__detect_kempston__
CustKempston$:
        AND   #0x1F
        OR    L
        LD    L,A
        RET
KEY1F$: ;��.���� �����,��� ������,��� ����������
        .DB   0xDF,0x01,0x01 ;P
        .DB   0xEF,0x08,0x01 ;7
        .DB   0xDF,0x02,0x02 ;O
        .DB   0xEF,0x10,0x02 ;6
        .DB   0xFD,0x01,0x04 ;A
        .DB   0xEF,0x04,0x04 ;8
        .DB   0xFB,0x01,0x08 ;Q
        .DB   0xEF,0x02,0x08 ;9
        .DB   0x7F,0x04,0x10 ;M
        .DB   0x7F,0x01,0x10 ;Space
        .DB   0xBF,0x01,0x10 ;Enter
        .DB   0xEF,0x01,0x10 ;0
        .DB   0xFB,0x08,0x20 ;R
        .DB   0
__endasm;
} //Control_Get

#ifdef __detect_kempston__
void Control__init (void) {
__asm
; AUTOconfig
      LD     HL,#__KEMPSTON
      LD     (HL),#0xC9   ;RET
      LD     B,#250
A_config01$:
      IN     A,(#0x1F)
      AND    #0x1F
      RET    NZ
      DJNZ   A_config01$
      LD     (HL),#0xDB   ;IN
__endasm;
} //Control__init
#endif //__detect_kempston__
