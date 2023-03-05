//#include "Config.oh"


#define pPixelsBuff 0xFA0F  // адрес массива изображения реж. 2


void GrTiles_DrawTile_fastcall (/*unsigned char x, unsigned char y,*/ unsigned char *tile) __z88dk_fastcall;

/*================================== Header ==================================*/

void GrTiles_DrawTile_fastcall (/*unsigned char x, unsigned char y,*/ unsigned char *tile) __naked __z88dk_fastcall {
#asm
        xchg        // DE = tile address
PUBLIC  _GrTiles_x  // x (in tiles, not in pixels)
PUBLIC  _GrTiles_y  // y (in tiles, not in pixels)
        DB   0x01   // LXI BC, yx
_GrTiles_x:
        DB   0      // C = x
_GrTiles_y:
        DB   0      // B = y
        // вычисляем адрес видеопамяти
        mov     A, B
        add     A
        add     B      // * 6
        add     A
        mov     B, A   // y

        rar
        rar
        rar
        ani     0x1F
        mov     H, A            // HI = (Y / 8) * 256

        mov     A, B
        ani     7
        mov     L, A            // LO = Y % 8

        mov     A, C
        ral                     // версия для текстовых координат X
        ral
        ral                     // A = x * 8
        ani     0xF8
        add     L
        mov     L, A            // LO = (Y % 8) + (X *8)

        // прибавляем текущий адрес видеопамяти
        lda     pPixelsBuff
        add     L
        mov     L, A
        lda     pPixelsBuff+1
        adc     H
        mov     H, A

        // переносим битовый образ
        push    H
        call    cpydata
        // выводим цвет
        pop     H
        mov     A, H
        xri     0x20
        mov     H, A            // HL - адрес в массиве цвета
        call    cpydata
        ret

    nextchank:
        mvi     A, 248          // HL += 256-8
        add     L
        mov     L, A
        mov     A, H
        aci     0
        mov     H, A
        ret

    cpydata:
        // выводим левую часть спрайта (12 линий)
        mov     B, H
        mov     C, L
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D

        // выводим правую часть спрайта (12 линий)
        mov     H, B
        mvi     A, 8
        add     C
        mov     L, A             // HL = BC + 8

        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        inx     H
        mov     A, L
        ani     7
        cz      nextchank
        // выводим 2 строки
        ldax    D
        mov     M, A
        inx     D
        inx     H                // поменять все на INR L
        ldax    D
        mov     M, A
        inx     D
        ret
#endasm
} //GrTiles_DrawTile_fastcall
