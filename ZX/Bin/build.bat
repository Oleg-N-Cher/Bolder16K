@IF /%XDev%==/ GOTO noxdev

@SET Name=Bolder16K
@SET Modules=Rsrc.rel GrApp.rel GrTiles.rel Control.rel Timer.rel Sound.rel Console.rel Labirint.rel
@SET CodeAddr=24100
@SET DataAddr=23296
@SET Bin=%XDev%\ZXDev\Bin
@SET Lib=%XDev%\ZXDev\Lib

@IF %1==%Name% GOTO build
@SET Name=TestTiles
@IF %1==%Name% GOTO build
@SET Name=Bolder16K
@CALL ..\Bin\compile %1

:build

%Bin%\sdcc %Name%.c -mz80 --code-loc %CodeAddr% --data-loc %DataAddr% --opt-code-speed --reserve-regs-iy --disable-warning 59 --disable-warning 84 --disable-warning 85 -I ..\C -I %Lib%\C -I "." -L %Lib% %Modules%
@IF errorlevel 1 PAUSE

%Bin%\hex2bin %Name%.ihx
::%Bin%\bin2tap -c 24099 -a %CodeAddr% -r %CodeAddr% -b -o ..\%Name%.tap %Name%.bin
..\Bin\GenLoader
IF errorlevel 1 PAUSE
@START ..\%Name%.tap
@GOTO exit

:noxdev
@ECHO Please set system variable XDev=X:\Path\To\XDev
@PAUSE

:exit
