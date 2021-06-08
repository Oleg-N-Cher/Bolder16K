MODULE GenLoader; (*$MAIN*)

IMPORT
  IO := Console, TapeTAP, Files, SYSTEM;

CONST
  LoaderStartLine  =      0;
  CodeStartAddr    =  24100;
  CodeMinStartAddr =  23900;
  CodeMaxStartAddr = 0FFFFH;
  CodeMaxSize      = CodeMaxStartAddr - CodeMinStartAddr + 1;

VAR
  loader: ARRAY 1024 OF BYTE; loaderLen: INTEGER;
  code: ARRAY CodeMaxSize OF BYTE; codeLen: INTEGER;
  screen: ARRAY 6912 OF BYTE;
  loaderFile, codeFile: Files.FileToRead;
  tap: TapeTAP.TapeFile;

BEGIN

  (* LOAD "DURAK" *)

  loaderFile.OpenToRead("..\Bin\BasicLoader.bas");
  IF loaderFile.error OR loaderFile.end THEN
    IO.WriteStr("Can't open file '..\Bin\BasicLoader.bas'."); IO.WriteLn;
    HALT(1)
  END;
  loaderLen := 0;
  WHILE ~ (loaderFile.error OR loaderFile.end) DO
    loader[loaderLen] := loaderFile.ReadByte(); INC(loaderLen);
  END;
  IF loaderFile.error THEN
    loaderFile.Close;
    IO.WriteStr("Can't read file '..\Bin\BasicLoader.bas'."); IO.WriteLn;
    HALT(1)
  END;
  loaderFile.Close;

  (*DEC(loaderLen, 8); (* DD E5 DD 21 00 00 DD 39: present if not use IY *)
  SYSTEM.MOVE(SYSTEM.ADR(loader[8]), SYSTEM.ADR(loader[0]), loaderLen);*)
  DEC(loaderLen, 1); (* DD E1 C9: present if not use IY *)

 (* LOAD "Screen"SCREEN$ *)

  codeFile.OpenToRead("..\Bin\Screen.bin");
  IF codeFile.error OR codeFile.end THEN
    IO.WriteStr("Can't open file 'Screen.bin'."); IO.WriteLn; HALT(1)
  END;
  codeLen := 0;
  WHILE ~ (codeFile.error OR codeFile.end) DO
    screen[codeLen] := codeFile.ReadByte(); INC(codeLen);
  END;
  IF codeFile.error THEN
    codeFile.Close;
    IO.WriteStr("Can't read file 'Screen.bin'."); IO.WriteLn; HALT(1)
  END;
  codeFile.Close;
  IF codeLen # 6912 THEN
    IO.WriteStr("The file 'Screen.bin' is not screen"); IO.WriteLn; HALT(1)
  END;

  (* LOAD "Bolder16K"CODE *)

  codeFile.OpenToRead("Bolder16K.bin");
  IF codeFile.error OR codeFile.end THEN
    IO.WriteStr("Can't open file 'Bolder16K.bin'."); IO.WriteLn; HALT(1)
  END;
  codeLen := 0;
  WHILE ~ (codeFile.error OR codeFile.end) DO
    code[codeLen] := codeFile.ReadByte(); INC(codeLen);
  END;
  IF codeFile.error THEN
    codeFile.Close;
    IO.WriteStr("Can't read file 'Bolder16K.bin'."); IO.WriteLn; HALT(1)
  END;
  codeFile.Close;

  (* SAVE "DURAK" *)

  tap.ReCreate("..\Bolder16K.tap");
  IF tap.error THEN
    IO.WriteStr("Can't create tape file"); IO.WriteLn; HALT(1)
  END;
  tap.SaveBasic("Bolder16K", LoaderStartLine, loaderLen, @loader);
  tap.SaveCode("Screen", 4000H, 6912, @screen);
  tap.SaveCode("Bolder16K", CodeStartAddr, codeLen, @code);
  tap.Finalize;
  IF tap.error THEN
    IO.WriteStr("Can't save tape file"); IO.WriteLn; HALT(1)
  END;
  HALT(0);

END GenLoader.
