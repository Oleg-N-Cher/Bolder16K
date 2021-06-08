MODULE Tiles; IMPORT IO := Console; (*$MAIN*)

VAR
  colors: ARRAY 4 OF INTEGER;
  map: ARRAY 12, 12+1 OF CHAR;
  n: INTEGER;

TYPE
  HexType = ARRAY 16 OF CHAR;

CONST
  Hex = HexType (
    "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"
  );

PROCEDURE WriteHex (i: INTEGER);
BEGIN
  IO.WriteStr("0x"); IO.WriteCh(Hex[i DIV 16]); IO.WriteCh(Hex[i MOD 16]);
END WriteHex;

PROCEDURE Emit (i: INTEGER);
BEGIN
  WriteHex(i); IO.WriteCh(",");
END Emit;

PROCEDURE Do (c0, c1, c2, c3: INTEGER);
  VAR x, y, CountPix, TekByte: INTEGER;
BEGIN
  colors[0] := c0; colors[1] := c1; colors[2] := c2; colors[3] := c3;
  CountPix := 0; TekByte := 0;
  FOR y := 0 TO LEN(map, 0)-1 DO
    FOR x := 0 TO LEN(map, 1)-2 DO
      INC(CountPix);
      CASE colors[ORD(map[y, x]) - 30H] OF
      | 0:
      | 1: CASE CountPix OF
            | 1: INC(TekByte, 8);
            | 2: INC(TekByte, 4);
            | 3: INC(TekByte, 2);
            | 4: INC(TekByte, 1);
           END;
      | 2: CASE CountPix OF
            | 1: INC(TekByte, 128);
            | 2: INC(TekByte, 64);
            | 3: INC(TekByte, 32);
            | 4: INC(TekByte, 16);
           END;
      | 3: CASE CountPix OF
            | 1: INC(TekByte, 128 + 8);
            | 2: INC(TekByte, 64 + 4);
            | 3: INC(TekByte, 32 + 2);
            | 4: INC(TekByte, 16 + 1);
           END;
      END;
(* 1 пиксел цвет: 128+8//2 пиксел цвет: 64+4//3 пиксел цвет: 32+2//4 пиксел цвет: 16+1 *)
      IF CountPix = 4 THEN
        CountPix := 0; Emit(TekByte); TekByte := 0;
      END;
    END;
    IF CountPix # 0 THEN Emit(TekByte) END;
  END;
END Do;

PROCEDURE Do2 (c0, c1, c2, c3: INTEGER);
  VAR x, y, CountPix, TekByte: INTEGER;
BEGIN
  colors[0] := c0; colors[1] := c1; colors[2] := c2; colors[3] := c3;
  FOR y := 0 TO LEN(map, 0)-1 DO
    CountPix := 2; TekByte := 0;
    FOR x := 0 TO LEN(map, 1)-2 DO
      INC(CountPix);
      CASE colors[ORD(map[y, x]) - 30H] OF
      | 0:
      | 1: CASE CountPix OF
            | 1: INC(TekByte, 8);
            | 2: INC(TekByte, 4);
            | 3: INC(TekByte, 2);
            | 4: INC(TekByte, 1);
           END;
      | 2: CASE CountPix OF
            | 1: INC(TekByte, 128);
            | 2: INC(TekByte, 64);
            | 3: INC(TekByte, 32);
            | 4: INC(TekByte, 16);
           END;
      | 3: CASE CountPix OF
            | 1: INC(TekByte, 128 + 8);
            | 2: INC(TekByte, 64 + 4);
            | 3: INC(TekByte, 32 + 2);
            | 4: INC(TekByte, 16 + 1);
           END;
      END;
(* 1 пиксел цвет: 128+8//2 пиксел цвет: 64+4//3 пиксел цвет: 32+2//4 пиксел цвет: 16+1 *)
      IF CountPix = 4 THEN
        CountPix := 0; Emit(TekByte); TekByte := 0;
      END;
    END;
    IF CountPix # 0 THEN Emit(TekByte) END;
  END;
END Do2;

BEGIN
  n := -1; (* Grass *)
  INC(n); map[n] := "001010101010";
  INC(n); map[n] := "010101010001";
  INC(n); map[n] := "101010101010";
  INC(n); map[n] := "010101110101";
  INC(n); map[n] := "101010101010";
  INC(n); map[n] := "011101011101";
  INC(n); map[n] := "101010101010";
  INC(n); map[n] := "010101110101";
  INC(n); map[n] := "101010101010";
  INC(n); map[n] := "000111010101";
  INC(n); map[n] := "101010100010";
  INC(n); map[n] := "010101010100";

  n := -1; (* Stone *)
  INC(n); map[n] := "000000000000";
  INC(n); map[n] := "000021210000";
  INC(n); map[n] := "000232121000";
  INC(n); map[n] := "002323212100";
  INC(n); map[n] := "023232321210";
  INC(n); map[n] := "012323212020";
  INC(n); map[n] := "021232121210";
  INC(n); map[n] := "012121202020";
  INC(n); map[n] := "021212121210";
  INC(n); map[n] := "002120202100";
  INC(n); map[n] := "000212121000";
  INC(n); map[n] := "000021210000";
  Do2(0, 2, 1, 3);
END Tiles.
