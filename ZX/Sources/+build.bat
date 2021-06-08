@ECHO OFF
IF NOT "%ZCCCFG%"=="" GOTO z88dk
ECHO Please install z88dk and set up the system variable ZCCCFG
PAUSE
EXIT

:z88dk

SET MainMod=Bolder16K
SET Mod=Console.asm Control.asm GrApp.asm GrTiles.asm Rsrc.asm Sound.asm Timer.asm Labirint.asm %MainMod%.asm
SET CC=zcc +zx -vn -startup=31 -clib=sdcc_iy -lmath32 -create-app -pragma-include:zpragma.inc
%CC% %Mod% -o%MainMod%
IF errorlevel 1 PAUSE

IF EXIST Bolder16K_CODE.bin MOVE /Y Bolder16K_CODE.bin Bolder16K.bin
IF EXIST Bolder16K_DATA.bin DEL Bolder16K_DATA.bin
IF EXIST Bolder16K_UNASSIGNED.bin DEL Bolder16K_UNASSIGNED.bin
IF EXIST ..\Bin\GenLoader.exe ..\Bin\GenLoader.exe
