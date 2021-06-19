//#include "Config.oh"
#include "GrApp.oh"

void Control_ChangePalette (void);
unsigned char Control_Get (void);
unsigned char Control_GetCustom (void);
unsigned char Control_PressedAnyKey (void);
unsigned char Control_ReadKey (void);
/*================================== Header ==================================*/

void Control_ChangePalette (void) {
#asm
#endasm
} //Control_ChangePalette

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_PressedAnyKey (void) {
#asm
/*
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
*/
#endasm
} //Control_PressedAnyKey

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_ReadKey (void) { // With auto-repeat
#asm
/*
{процедура опроса основной клавиатуры на нажатие любой клавиши}
LabelA(pKeyO);
MviA($00);Sta(bKeyProtect);
Out_($D0);In_($D1);
Xri($FF);
Sta(bKeyProtect);
RET;
*/
#endasm
} //Input_Read_Repeat

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_Get (void) {
#asm
        ;CALL _Control_ChangePalette
// Опрос дополнительной клавиатуры на нажатие "стрелок"
        MVI  A, 0xF7
        OUT  0xD2
        IN   0xD2
        CMA
        ANI  0xF0
        MOV  L, A
#endasm
} //Control_Get

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_GetCustom (void) {
#asm
        ;CALL _Control_ChangePalette
// Опрос дополнительной клавиатуры на нажатие "стрелок"
        MVI  A, 0xF7
        OUT  0xD2
        IN   0xD2
        CMA
        ANI  0xF0
        MOV  L, A
#endasm
} //Control_GetCustom