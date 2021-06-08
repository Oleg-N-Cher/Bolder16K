#include "Config.oh"

void GrTiles_DrawTile_fastcall (/*unsigned char x, unsigned char y,*/ unsigned char *tile) __z88dk_fastcall;

/*================================== Header ==================================*/

void GrTiles_DrawTile_fastcall (/*unsigned char x, unsigned char y,*/ unsigned char *tile) __naked __z88dk_fastcall {
#asm
        XCHG        ; DE = tile address
PUBLIC  _GrTiles_x  ; x (in tiles, not in pixels)
PUBLIC  _GrTiles_y  ; y (in tiles, not in pixels)
        DB   0x01   ; LXI BC, yx
_GrTiles_x:
        DB   0      ; C = x
_GrTiles_y:
        DB   0      ; B = y
        MOV  A, B   ; y
        ADD  A
        ADD  B      ; * 6
        ADD  A
        MOV  L, A   ; HL = #TAB[y * 6]
        MVI  H, Config_ScreenTable
        MOV  A, C
        RRA         ; x DIV 2
        JC   DRAWTILE2
        ADD  C
        ADD  M      ; x + x DIV 2
        INR  H
        MOV  H, M   ; high screen addr byte
        MOV  L, A   ; low screen addr byte
        XRA  A
        OUT  0xC2   ; Включить видео ОЗУ
        LXI  B, 0x0040-2
        MVI  A, 12
DRAWLOOP:
        STA  (ROWLOOP+1)
        LDAX D      ; 1st
        MOV  M, A
        INX  H
        INX  D
        LDAX D      ; 2nd
        MOV  M, A
        INX  H
        INX  D
        LDAX D      ; 3rd
        MOV  M, A
        INX  D
        DAD  B
ROWLOOP:
        MVI  A, 12
        DCR  A
        JNZ  DRAWLOOP
        MVI  A, 2
        OUT  0xC2   ; Отключить видео ОЗУ
        RET
DRAWTILE2:
        ADD  C
        ADD  M
        INR  H
        MOV  H, M   ; high screen addr byte
        MOV  L, A   ; low screen addr byte
        INR  D
        INR  D
        INR  D      ; 2nd set of tiles + PAD
        XRA  A
        OUT  0xC2   ; Включить видео ОЗУ
        LXI  B, 0x0040-3
        MVI  A, 12
DRAWLOOP2:
        STA  (ROWLOOP2+1)
        XCHG        ; HL = tile address
        LDAX D      ; 1st
        ANI  0xCC
        ORA  M
        STAX D
        INX  H
        INX  D
        MOV  A, M   ; 2nd
        STAX D
        INX  H
        INX  D
        MOV  A, M   ; 3rd
        STAX D
        INX  H
        INX  D
        LDAX D      ; 4th
        ANI  0x33
        ORA  M
        STAX D
        INX  H
        XCHG
        DAD  B
ROWLOOP2:
        MVI  A, 12
        DCR  A
        JNZ  DRAWLOOP2
        MVI  A, 2
        OUT  0xC2   ; Отключить видео ОЗУ
        RET
#endasm
} //GrTiles_DrawTile_fastcall
