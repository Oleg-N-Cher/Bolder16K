@ECHO OFF
SET Debug=TRUE
SET Clean=FALSE
SET Pause=FALSE
SET CodeAdr=256
SET Modules=Labirint.o Control.o Rsrc.o GrApp.o GrTiles.o Console.o
SET MainMod=Bolder16K
SET Include=-I..\C
SET FileExt=com

SET K580Dev=%XDev%\K580Dev
IF "%XDev%"=="" SET K580Dev=..

IF "%MainMod%"=="" SET MainMod=%1
IF "%MainMod%"=="%1" GOTO Build

:Compile

SET SaveOptions=%Options%
SET SaveInclude=%Include%
CALL %K580Dev%\Bin\Compile.bat %1
SET Options=%SaveOptions%
SET Include=%SaveInclude%

:Build

IF "%CodeAdr%"=="" SET CodeAdr=0
SET Options=%Options% -zorg=%CodeAdr% -O3
SET Include=%Include% -I%K580Dev%\Lib\C -I%K580Dev%\Lib\Obj
SET Libraries=%Libraries% -L%K580Dev%\Lib
IF "%Clean%"=="" SET Clean=TRUE
IF "%Start%"=="" SET Start=TRUE
IF "%Pause%"=="" SET Pause=FALSE
IF "%FileExt%"=="" SET FileExt=rk

SET CC=zcc.exe +rk86 %Options% %Modules% %Libraries%

IF EXIST %MainMod% GOTO Config

%CC% %MainMod%.c -o ..\%MainMod%.com -I. -I..\Lib -I%K580Dev%\Lib %Include%
GOTO Link

:Config

%CC% %MainMod%.c -o ..\%MainMod%.com -I%MainMod% %Include%

:Link

IF errorlevel 1 PAUSE

IF "%FileExt%"=="lvt" GOTO Lviv
IF "%FileExt%"=="com" GOTO PK8000

:RK86
%K580Dev%\Bin\bin2rk.exe %MainMod%.bin >NUL
MOVE %MainMod%.rk ..\%MainMod%.%FileExt% >NUL
GOTO AfterLink

:Lviv
%K580Dev%\Bin\MakeLvov\MakeLvov.exe %MainMod% %CodeAdr% >NUL
MOVE %MainMod%.lvt .. >NUL

:PK8000
IF "%Debug%"=="TRUE" MOVE /Y ..\%MainMod%.com ..\B.com && SET MainMod=B
..\Bin\C8000W.EXE -r "d:\WIN32APP\Emulz\b2m\PK8000\CF.CPM" A: ..\%MainMod%.com

:AfterLink

IF NOT "%Clean%"=="TRUE" GOTO Done
DEL *.bin %MainMod%.oh %MainMod%.o
IF "%Modules%"=="" DEL %MainMod%.c

:Done

IF "%Pause%"=="TRUE" PAUSE
IF "%Start%"=="TRUE" d:\WIN32APP\Emulz\b2m\EMU.exe ..\Bin\PK8000.emu
