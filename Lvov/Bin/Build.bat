@ECHO OFF
IF NOT "%XDev%"=="" GOTO XDev
ECHO Please set system variable XDev=X:\Path\To\XDev
PAUSE
EXIT

:XDev

SET CodeAdr=32768
SET Modules=Labirint.o Control.o Rsrc.o GrApp.o GrTiles.o Console.o
SET MainMod=Bolder16K
SET Include=-I..\C
SET FileExt=lvt
CALL %XDev%/K580Dev/Bin/Build.bat %1
SET Options=-S
SET Start=FALSE
%XDev%/K580Dev/Bin/Build.bat %1
