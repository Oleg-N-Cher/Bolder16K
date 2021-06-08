@ECHO OFF
IF NOT "%XDev%"=="" GOTO XDev
ECHO Please set system variable XDev=X:\Path\To\XDev
PAUSE
EXIT

:XDev

SET MainMod=Bolder16K
SET Include=-I..\C
CALL %XDev%\K580Dev\Bin\Compile.bat %1
MOVE /Y ..\C\%1.o
