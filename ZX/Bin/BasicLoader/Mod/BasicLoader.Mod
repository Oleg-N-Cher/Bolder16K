MODULE BasicLoader; (*$MAIN*)
IMPORT b := Basic;

(* POKE 23739, 111 - readdress output to NUL: useful for loader
https://zx-pk.ru/threads/32967-zagruzchik-48k-i-zastavka.html
*)

CONST
  CodeName      = "Bolder16K";
  CodeLoadAddr  = 24100;
  CodeStartAddr = 24100;

CONST
  Cr        =  0DX;
  Num       =  0EX;
  At        =  16X;
  SCREEN    = 0AAX;
  PI        = 0A7X;
  CODE      = 0AFX;
  USR       = 0C0X;
  NOT       = 0C3X;
  BORDER    = 0E7X;
  POKE      = 0F4X;
  RANDOMIZE = 0F9X;
  CLEAR     = 0FDX;
  LOAD      = 0EFX;
  PRINT     = 0F5X;(*
  CLS       = 0FBX;*)

BEGIN
  (* 0 POKE [0]23693,NOT PI: BORDER NOT PI: CLEAR 0[24299] *)
  b.DATA2(0, 0); b.DATAW(63);
  b.DATACH5(POKE, "0", Num, 0X, 0X); b.DATAW(23693); b.DATA(0);
  b.DATACH8(",", NOT, PI, ":", BORDER, NOT, PI, ":");
  b.DATACH5(CLEAR, "0", Num, 0X, 0X); b.DATAW(CodeLoadAddr - 1); b.DATA(0);

  (* POKE 23739, 111 *)
  b.DATACH2(":", POKE); b.DATACH4("0", Num, 0X, 0X); b.DATAW(23739);
  b.DATA(0); b.DATACH5(",", "0", Num, 0X, 0X); b.DATAW(111); b.DATA(0);

  (* : LOAD ""SCREEN$ *)
  b.DATACH2(":", LOAD); b.DATA2(ORD('"'), ORD('"')); b.DATACH(SCREEN);

  (* : LOAD ""CODE: RANDOMIZE USR 0[CodeLoadAddr] *)
  (*b.DATACH2(":", PRINT); b.DATA5(22H, ORD(At), 0, 0, 22H); ";" *)
  b.DATACH2(":", LOAD); b.DATA2(ORD('"'), ORD('"'));
  b.DATACH2(CODE, ":");

  (*b.DATACH3(0F2X, NOT, PI);*)

  b.DATACH3(RANDOMIZE, USR, "0");
  b.DATACH3(Num, 0X, 0X); b.DATAW(CodeLoadAddr); b.DATA(0);

  b.DATACH(Cr);
END BasicLoader.
