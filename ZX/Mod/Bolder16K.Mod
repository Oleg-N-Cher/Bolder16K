MODULE Bolder16K; (*$MAIN*)
IMPORT
  Scr := GrApp, Gr := GrTiles, IO := Console, Labirint,
  Rsrc, Ctrl := Control, Timer, Sound, SYSTEM;

  TYPE BYTE = Rsrc.NATINT;

  VAR
    level, menu: BYTE; pressed: Ctrl.Keys;

PROCEDURE DrawPointer;
BEGIN
  IO.At(10, menu + 4); IO.WriteCh(">");
END DrawPointer;

PROCEDURE PressAnyKey;
BEGIN
  REPEAT UNTIL Ctrl.GetCustom() # {}; Sound.KeyPressed;
END PressAnyKey;

PROCEDURE Menu (): BOOLEAN;
BEGIN
  LOOP
    IO.Clear;
    IO.Colors(IO.LMagenta);
    IO.At(10, 0); IO.WriteStr("BOLDER DASH");
    IO.Colors(IO.LWhite);
    IO.At(12, 4); IO.WriteStr("PLAY");
    IO.At(12, 5); IO.WriteStr("CONTROL");
    IO.At(12, 6); IO.WriteStr("ABOUT");
    IO.At(12, 7); IO.WriteStr("EXIT");
    IO.Colors(IO.LCyan);
    IO.At(0, 11); IO.WriteStr(7FX+"A.Melentiev, Oleg N. Cher, 2021");
    menu := 0;
    LOOP
      DrawPointer;
      pressed := Ctrl.GetCustom();
      IF (pressed = {Ctrl.Up}) & (menu # 0) THEN
        IO.At(10, menu + 4); IO.WriteCh(" ");
        DEC(menu); DrawPointer; Sound.KeyPressed; Timer.Start(4); Timer.Until;
      ELSIF (pressed = {Ctrl.Down}) & (menu # 3) THEN
        IO.At(10, menu + 4); IO.WriteCh(" ");
        INC(menu); DrawPointer; Sound.KeyPressed; Timer.Start(4); Timer.Until;
      ELSIF pressed = {Ctrl.Fire} THEN Sound.KeyPressed;
        CASE menu OF
        | 0: RETURN TRUE
        | 1: Scr.Cls;
          IO.Colors(IO.LMagenta);
          IO.At(1, 2); IO.WriteStr("Keyboard: Q,A,O,P - directions");
          IO.Colors(IO.LCyan);
          IO.At(1, 4); IO.WriteStr("M, Space - select, R - restart");
          IO.Colors(IO.Yellow);
          IO.At(1, 6); IO.WriteStr("1, 2 - change in - game colors");
          IO.Colors(IO.LWhite);
          IO.At(1, 8); IO.WriteStr("Joysticks: Kempston/Sinclair 2");
          PressAnyKey; Scr.Cls; EXIT
        | 2: Scr.Cls;
          IO.Colors(IO.LMagenta);
          IO.At(1, 0); IO.WriteStr('This game called "Bolder Dash"');
          IO.Colors(IO.LCyan);
          IO.At(2, 1); IO.WriteStr("was originally developed by");
          IO.Colors(IO.Yellow);
          IO.At(0, 2); IO.WriteStr("A.V.Melentiev for Soviet retro-");
          IO.Colors(IO.LWhite);
          IO.At(1, 3); IO.WriteStr('computer "Electronica BK-0010".');
          IO.Colors(IO.LMagenta);
          IO.At(0, 4); IO.WriteStr("Wladimir Mutel, inspired by the");
          IO.Colors(IO.LCyan);
          IO.At(3, 5); IO.WriteStr("game, performed its manual");
          IO.Colors(IO.Yellow);
          IO.At(1, 6); IO.WriteStr("disassembly and port to Soviet");
          IO.Colors(IO.LWhite);
          IO.At(0, 7); IO.WriteStr("computer Poisk-1 (IBM XT clone).");
          IO.Colors(IO.LMagenta);
          IO.At(2, 8); IO.WriteStr("http://goldies.ru/games/1329");
          IO.Colors(IO.LCyan);
          IO.At(1, 9); IO.WriteStr("I made this Spectrum 16K port");
          IO.Colors(IO.Yellow);
          IO.At(0, 10); IO.WriteStr("for Concurso juegos ASM 2021 !!!");
          IO.Colors(IO.LWhite);
          IO.At(9, 11); IO.WriteStr("No pasaran! :>");
          PressAnyKey; Scr.Cls; EXIT
        | 3: Scr.Cls; RETURN FALSE
        ELSE END;
      END;
      Timer.Start(4); Timer.Until;
    END;
  END;
END Menu;

BEGIN
  LOOP
    IF ~Menu() THEN EXIT (* Game *) END;
    Labirint.lives := 5; level := 0;
    LOOP (* One game *)
      IF Labirint.Play(level) THEN
        INC(level);
        IF level = Rsrc.MaxLevelNumber THEN
          IO.Colors(IO.LCyan); IO.Clear;
          IO.At(14, 5); IO.WriteStr("YOU");
          IO.At(14, 6); IO.WriteStr("WIN!");
          EXIT
        END;
      ELSIF Labirint.lives = 0 THEN
        IO.Colors(IO.LWhite); IO.Clear;
        IO.At(14, 5); IO.WriteStr("GAME");
        IO.At(14, 6); IO.WriteStr("OVER");
        EXIT
      END;
    END;
    PressAnyKey; Scr.Cls;
  END;
  Ctrl.Close; Scr.Close;
END Bolder16K.
