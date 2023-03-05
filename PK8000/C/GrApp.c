/* Ver 1.0.0 for ZX Spectrum 48/128 */
/* Use ZXDev to compile this module */

#include "Timer.oh"
#include "Config.oh"



#define SCRBUF_ADDR     0x9800  // адрес буфера экрана (реж. 2)
#define PIXBUF_ADDR     0x8000  // массив изображения для режима 2
#define COLBUF_ADDR     0xA000  // массив цвета для режима 2

/*
  системные переменные управления курсором в текстовых видеорежимах
*/
#define flCurHide       0xFDBE  // флаг видимости/скрытия курсора (FF - скрыт)
#define bCurBkGr        0xFA1C  // символ фона под курсором
#define pCurStored      0xFA1E  // адрес видеопамяти сохраненного фона под курсором
#define bCurPosX        0xFA21  // положение курсора на экране
#define bCurPosY        0xFA22

#define bVideoMode      0xFD8C  // номер текущего видеорежима

/*
  блок параметров текущего видеорежима (VIDMODE)
*/
#define pVideoParam     0xFA00  // начало блока параметров
#define VIDPARSIZE      19      // и его размер
// сам блок
#define bScrWidth       0xFA00  // полная ширина экрана, включая не отображаемые области
#define bHideLeft       0xFA01  // кол. не отображаемых символов слева
#define bLogWidth       0xFA02  // видимая ширина экрана
#define bLogHeight      0xFA03  // кол. строк экрана
#define bHideRight      0xFA04  // кол. не отображаемых символов справа
#define pScrBuf0        0xFA05  // адрес буфера экрана реж. 0 и 1
#define pTabColor       0xFA07  // адрес таб. цвета реж. 1
#define pCharGen        0xFA09  // адрес знакогенератора реж. 0 и 1,
#define pScrBuf2        pCharGen// или буфера экрана реж. 2
#define pPixelsBuff     0xFA0F  // адрес массива изображения реж. 2
#define pColorsBuff     0xFA11  // адрес массива цвета реж. 2




typedef struct {
  char         fwidth;          // полная ширина экрана, включая не отображаемые области
  char         lhide;           // кол. не отображаемых символов слева
  char         scrwidth;        // видимая ширина экрана
  char         height;          // кол. строк экрана
  char         rhide;           // кол. пропускаемых символов справа
  unsigned int bufScr0;         // адрес буфера экрана (реж. 0 и 1)
  unsigned int tabCol1;         // адрес таблицы цвета (реж. 1)
  unsigned int bufScr2;         // адрес буфера экрана (реж. 2) или адрес знакогенератора (реж. 0 и 1)
  unsigned int res1;
  unsigned int res2;
  unsigned int bufImg2;         // массив изображения для режима 2
  unsigned int bufCol2;         // массив цвета для режима 2
  char         nVidMode;        // номер видеорежима
} VID_TABLE;


VID_TABLE tabMode0 = {64,0,40,24,24,0xE000,0xE400,0xF000,0,0,0,0,0};
VID_TABLE tabMode2 = {32,0,32,24,00,0,0,SCRBUF_ADDR,0,0,PIXBUF_ADDR,COLBUF_ADDR,2};




void GrApp__init (void);
void GrApp_Close (void);
void GrApp_Cls (void);


static void vidSetMode (void *tab) __z88dk_fastcall;
static void vidInitScrBuf (void);

//void GrApp_ScrollDown (unsigned char lines) __z88dk_fastcall;
//void GrApp_ScrollUp (unsigned char lines) __z88dk_fastcall;


void GrApp__init (void) {
#asm
        call    _GrApp_Cls
        di
        lxi     H, _tabMode2
        call    _vidSetMode      // устанавливаем регистры и переменные
        call    _vidInitScrBuf   // инициализируем буфер экрана (768 байт)
        call    _GrApp_Cls      // инициализируем массив изображения
        // устанавливаем палитру
        mvi     C, 0x0F         // белый текст на черном фоне
        call    _GrApp_ClsCol
        // set border color
        xra     A
        out     0x88
        // гасим экран
        in      0x86
        ani     0xEF
        out     0x86
        // собственно переходим в граф. режим
        lda     pPixelsBuff+1
        ani     0xC0
        mov     B, A            // B = биты 14-15 адреса видео-ОЗУ
        in      0x84
        ani     0x0F
        ora     B
        ori     0x10            // выставляем бит граф. режима
        out     0x84
        ei
        // разрешаем отображение на экран
VidExit:
        in      0x86
        ori     0x10
        out     0x86
#endasm
} //GrApp__init

void GrApp_Close (void) __naked {
#asm
        call    _GrApp_Cls
        di
        lxi     H, _tabMode0
        call    _vidSetMode
        call    _GrApp_Cls
        // устанавливаем видеорежим 0
        lda     pScrBuf0+1
        ani     0xC0
        mov     B, A            // B = биты 14-15 адреса видео-ОЗУ
        in      0x84
        ani     0x0F
        ora     B
        ori     0x20            // текстовый, 40 символов
        out     0x84
        ei
        ; разрешаем отображение курсора
        mvi     A, 0
        sta     flCurHide
        jmp     VidExit
#endasm
} //GrApp__Close


void GrApp_Cls (void) {
#asm
        lda     bVideoMode
        cpi     2
        jnz     clstxt
        // очистка экрана для режима 2
        lhld    pPixelsBuff
        mvi     E, 0
        lxi     B, 6144         // три массива изобр. (знакогенератора) по 2048 байт (3 по 256*8)
    clsch2:
        mov     M, E
        inx     H
        dcx     B
        mov     A, C
        ora     B
        jnz     clsch2
        // теперь гасим палитру
        mvi     E, 0x0F         // дефолтный цвет
    clrcl:
        mov     A, E
        //sta     bTextAttr       // сохраняем цвет
        lhld    pColorsBuff     // HL - адрес таблицы цвета реж. 2
        lxi     B, 6144         // три массива изобр. (знакогенератора) по 2048 байт (3 по 256*8)
    clschc:
        mov     M, E
        inx     H
        dcx     B
        mov     A, C
        ora     B
        jnz     clschc

        jmp     rstcur

    clstxt:
        lhld    pScrBuf0
        cpi     1
        jnz     cls0
        // очистка экрана для режима 1
        lxi     B, 768          // 32*24
        mvi     E, 32
    clslp:
        mov     M, E
        inx     H
        dcx     B
        mov     A, B
        ora     C
        jnz     clslp

    rstcur:
        // устанавливаем курсор в верхний левый угол
        xra     A
        sta     bCurBkGr
        sta     bCurPosX
        sta     bCurPosY
        shld    pCurStored
        ret
    cls0:
        // очистка экрана для режима 0
        rnc
        mvi     C, 24
    cl0lp:
        // заполняем невидимую левую часть строки
        lda     bHideLeft
        mvi     B, 0
        call    cl0fil
        // заполняем видимую часть строки
        lda     bLogWidth
        mvi     B, ' '
        call    cl0fil
        // заполняем правую часть строки
        lda     bHideRight
        sui     5
        call    cl0fil
        mvi     A, 5            // заканчиваем строку кодами '5 6 0D 0E 00'
        mov     M, A
        inr     A               // 6
        inx     H
        mov     M, A
        mvi     A, 0x0D         // 0D
        inx     H
        mov     M, A
        inr     A               // 0E
        inx     H
        mov     M, A
        inx     H
        mvi     B, 0
        mov     M, B
        inx     H
        // переходим к следующей строке
        dcr     C
        jnz     cl0lp
        lhld    pScrBuf0
        jmp     rstcur

    cl0fil:
        ana     A
        rz
        mov     M, B
        inx     H
        dcr     A
        jnz     cl0fil
#endasm
} //GrApp_Cls

/*--------------------------------- Cut here ---------------------------------*/
void GrApp_ClsCol (unsigned char cAttr) __naked __z88dk_fastcall {
#asm
        mov     E, L
        jmp     clrcl
#endasm
}

/*--------------------------------- Cut here ---------------------------------*/
static void vidSetMode (void *tab) __z88dk_fastcall {
#asm
        mov     C, L
        mov     B, H
        // переносим таблицу параметров видеорежима в системную память
        // чтобы функции BIOS работали нормально
        lxi     H, pVideoParam
        mvi     E, VIDPARSIZE
    vsetlp:
        ldax    B
        inx     B
        mov     M, A
        inx     H
        dcr     E
        jnz     vsetlp
        ldax    B
        sta     bVideoMode
        // задаем адрес буфера экрана (режимы 0 и 1) в видео-ОЗУ
        lda     pScrBuf0+1
        rrc
        rrc
        out     0x90
        // адрес знакогенератора (режимы 0 и 1) или буфера экрана (режим 2) в видео-ОЗУ
        lda     pCharGen+1
        rrc
        rrc
        out     0x91
        // адрес массива графики (режим 2) в видео-ОЗУ
        lda     pPixelsBuff+1
        rrc
        rrc
        cma
        out     0x92
        // адрес массива цвета (режим 2) в видео-ОЗУ
        lda     pColorsBuff+1
        rrc
        rrc
        cma
        out     0x93
#endasm
} //vidSetMode

/*--------------------------------- Cut here ---------------------------------*/
static void vidInitScrBuf (void) {
#asm
        lhld    pScrBuf2
        mvi     B, 0
        mvi     C, 3
    fivbm:
        mov     M, B
        inx     H
        inr     B
        jnz     fivbm
        dcr     C
        jnz     fivbm
#endasm
} // vidInitScrBuf
