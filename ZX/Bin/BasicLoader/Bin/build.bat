@IF "%1"=="BasicLoader" GOTO ZXDev
@IF "%1"=="BasicLoaderEx" GOTO ZXDev

:WinDev

@SET PATH=%XDev%\WinDev\Bin\MinGW\bin;%PATH%
@SET Bin=%XDev%\WinDev\Bin\MinGW\bin
@SET Lib=%XDev%\WinDev\Lib

@SET MainMod=GenLoader
@IF "%1"=="GenLoaderEx" @SET MainMod=GenLoaderEx

@SET StripExe=-nostartfiles %XDev%\WinDev\Lib\Mod\crt1.c -Wl,-e__WinMain -D_WINGUI
@SET Options=%StripExe% -m32 -s -Os -g0 -fvisibility=hidden -fomit-frame-pointer -finline-small-functions -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-exceptions -Wl,--gc-sections -Wl,--file-alignment,512

%Bin%\gcc.exe %Options% TapeTAP.c %MainMod%.c -I %Lib%\Mod -I %Lib%\Obj -I ..\Lib %Lib%\XDev.a -o ..\..\%MainMod%.exe
@IF errorlevel 1 PAUSE
@GOTO exit

:ZXDev

@SET CodeAddr=60000
@SET DataAddr=65500
@SET Bin=%XDev%\ZXDev\Bin
@SET Lib=%XDev%\ZXDev\Lib

%Bin%\sdcc %1.c -mz80 --reserve-regs-iy --code-loc %CodeAddr% --data-loc %DataAddr% --opt-code-speed --no-std-crt0 -I ..\Lib -I %Lib%\C --disable-warning 59 --disable-warning 85 --disable-warning 126
@IF errorlevel 1 PAUSE

%Bin%\hex2bin %1.ihx
@MOVE %1.bin ..\..\%1.bas

:exit
