::@ECHO OFF
IF NOT "%ZCCCFG%"=="" GOTO z88dk
ECHO Please install z88dk and set up the system variable ZCCCFG
PAUSE
EXIT

:z88dk

CD ..\Obj
SET MainMod=Bolder16K
SET Mod=..\C\Console.c ..\C\Control.c ..\C\GrApp.c ..\C\GrTiles.c ..\C\Rsrc.c ..\C\Sound.c ..\C\Timer.c Labirint.c %MainMod%.c
IF EXIST .debug SET Opt=--max-allocs-per-node20
IF NOT EXIST .debug SET Opt=-SO3 --opt-code-size --max-allocs-per-node200000 -S
SET Lib=%XDev%\ZXDev\Lib
SET CC=zcc +zx -vn -startup=31 -clib=sdcc_iy -lmath32 -create-app %Opt% -pragma-include:zpragma.inc -Cs"--disable-warning 59" -Cs"--disable-warning 85" -Cs"--disable-warning 126" -Cs"--disable-warning 158"
%CC% -D_Z88 %Mod% -o%MainMod% -I..\C -I..\Obj -I%Lib%\C -I%Lib%\Obj -L%Lib%
::IF errorlevel 1 PAUSE

CD ..\Sources
IF EXIST ..\C\Console.c.asm MOVE /Y ..\C\Console.c.asm Console.asm
IF EXIST ..\C\Control.c.asm MOVE /Y ..\C\Control.c.asm Control.asm
IF EXIST ..\C\GrApp.c.asm MOVE /Y ..\C\GrApp.c.asm GrApp.asm
IF EXIST ..\C\GrTiles.c.asm MOVE /Y ..\C\GrTiles.c.asm GrTiles.asm
IF EXIST ..\C\Rsrc.c.asm MOVE /Y ..\C\Rsrc.c.asm Rsrc.asm
IF EXIST ..\C\Sound.c.asm MOVE /Y ..\C\Sound.c.asm Sound.asm
IF EXIST ..\C\Timer.c.asm MOVE /Y ..\C\Timer.c.asm Timer.asm
IF EXIST ..\Obj\Labirint.c.asm MOVE /Y ..\Obj\Labirint.c.asm Labirint.asm
IF EXIST ..\Obj\Bolder16K.c.asm MOVE /Y ..\Obj\Bolder16K.c.asm Bolder16K.asm

PAUSE
EXIT


IF EXIST %MainMod%.tap DEL %MainMod%.tap

..\Bin\z88CutBin\z88CutBin.exe ..\Obj\%MainMod%_CODE.bin


GenExoLoader.exe ..\..\Obj\%MainMod%.bin Exomizer\Exomizer.bin
CD ..\..\Obj
..\Bin\GenLoaderEx
IF errorlevel 1 PAUSE
START ..\%MainMod%.tap
