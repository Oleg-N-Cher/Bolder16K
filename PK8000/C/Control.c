//#include "Config.oh"
#include "GrApp.oh"

void Control_ChangePalette (void);
unsigned char Control_Get (void);
unsigned char Control_GetCustom (void);
unsigned char Control_PressedAnyKey (void);
unsigned char Control_ReadKey (void);
/*================================== Header ==================================*/


/*****************************************************************************
                      ЗАГЛУШКА ДЛЯ INTERRUPT
******************************************************************************/


#define INTMGR  0xFEDC      // адрес менеджера нашего IRQ
#define INTJMP  0xF86E      // переход на пользовательский обработчик прерывания
#define INTADR  0xF86F      // адрес пользовательского обработчика


/*
  адрес старого обработчика прерывания
*/
static unsigned char OldVecJmp;
static unsigned int  OldVecAddr;


/*
 Инициализация системы IRQ
*/
void /*InitIRQ*/ Control__init (void) __naked {
#asm
        // переносим наш обработчик в верхние адреса памяти
        lxi     D, IrqManager
        lxi     H, INTMGR
        mvi     C, IrqMngEnd-IrqManager
    sirql:
        ldax    D
        mov     M, A
        inx     D
        inx     H
        dcr     C
        jnz     sirql
        // сохраняем старый обработчик
        lda     INTJMP
        sta     _OldVecJmp
        lhld    INTADR
        shld    _OldVecAddr
        // ставим свой
        di
        mvi     A, 0xC3        // jmp
        sta     INTJMP
        lxi     H, INTMGR
        shld    INTADR
        ei
        ret

// Менеджер пользовательских прерываний, вызывается из ПЗУ
// при каждом прерывании
IrqManager:
        // убираем из стека адрес возврата в функцию BIOS,
        // теперь по RET будет выход из обработчика IRQ, пропустив
        // код обработчика BIOS
        xthl
        pop     H
        ei
        ret
IrqMngEnd:
#endasm
} //Control__init


/*
  Удаление своей системы IRQ
*/
void /*DoneIRQ*/ Control_Close (void) __naked {
#asm
        di
        lda     _OldVecJmp
        sta     INTJMP
        lhld    _OldVecAddr
        shld    INTADR
        ei
        ret
#endasm
} //Control_Close


/*****************************************************************************
                              КОНЕЦ ЗАГЛУШКИ
******************************************************************************/

void Control_ChangePalette (void) {
#asm
#endasm
} //Control_ChangePalette

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_PressedAnyKey (void) {
#asm
#endasm
} //Control_PressedAnyKey

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_ReadKey (void) { // With auto-repeat
#asm
#endasm
} //Input_Read_Repeat

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_Get (void) __naked {
#asm
        mvi     A, 7
        call    kbColumn
        rrc
        ani     00000010b
        mov     B, A
        mvi     A, 8
        call    kbColumn
        ani     11110001b
        ora     B
        rrc
        rrc
        rrc
        rrc
        mov     L, A
        ret

//------------------------------------------------------------------------
// чтение строки клавиатурной матрицы
//------------------------------------------------------------------------
// на входе:
//    A  - номер строки матрицы [0..9]
// на выходе:
//    A  - строка (единичные биты - нажатые клавиши)
//    C  - номер строки матрицы [0..9]
kbColumn:
        //ani     0Fh
        mov     C, A
        in      82h
        ani     0F0h
        ora     C
        out     82h
        in      81h
        cma
        ret
#endasm
} //Control_Get

/*--------------------------------- Cut here ---------------------------------*/
unsigned char Control_GetCustom (void) {
#asm
#endasm
} //Control_GetCustom