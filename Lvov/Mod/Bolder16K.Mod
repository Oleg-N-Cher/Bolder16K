MODULE Bolder16K; (*$MAIN*)
IMPORT
  Scr := GrApp, Gr := GrTiles, Ctrl := Control,
  Lvov, RK86, SYSTEM, Rsrc, Labirint;
VAR
  keys: SET; x, y: SYSTEM.BYTE;

PROCEDURE SetTable;
  VAR scr, tab: INT16; n, val: SYSTEM.BYTE;
BEGIN
  scr := 4707H;
  tab := 0;
  FOR n := 0 TO 254 DO
    val := scr MOD 100H; SYSTEM.PUT(tab, val);
    val := scr DIV 100H; SYSTEM.PUT(tab+100H, val); INC(tab);
    INC(scr, 256 DIV 4);
  END
END SetTable;

BEGIN
  SetTable;
  IF Labirint.Play(0) THEN END;
  x := 2; y := 2;
  LOOP
    keys := Ctrl.Get();
    Gr.DrawTile(x, y, Rsrc.None);
    IF (Ctrl.Right IN keys) & (x < 31) THEN INC(x) END;
    IF (Ctrl.Left IN keys ) & (x >  0) THEN DEC(x) END;
    IF (Ctrl.Up IN keys   ) & (y >  0) THEN DEC(y) END;
    IF (Ctrl.Down IN keys ) & (y < 31) THEN INC(y) END;
    (* Lvov.FIL_BOX(x, y, x+5, y+5, 3); *)
    Gr.DrawTile(x, y, Rsrc.Stone);
    RK86.WAIT(5000);
  END;
  Scr.Close
END Bolder16K.
