@IF %1==BasicLoader GOTO ZXDev

:WinDev

@SET Bin=%XDev%\WinDev\Bin\MinGW\bin
@SET Lib=%XDev%\WinDev\Lib
@SET CC=%Bin%\gcc -I %Lib%\Mod -I %Lib%\Obj -I ..\Lib

%CC% -c %1.c
@IF errorlevel 1 PAUSE
@GOTO exit

:ZXDev

@SET Bin=%XDev%\ZXDev\Bin
@SET Lib=%XDev%\ZXDev\Lib

%Bin%\sdcc %1.c -mz80 --opt-code-size --no-std-crt0 -I ..\Lib -I %Lib%\C -L %Lib% --disable-warning 59 --disable-warning 85 --disable-warning 126
@IF errorlevel 1 PAUSE

%Bin%\hex2bin %1.ihx

:exit
