void Timer_Until (void);
/*================================== Header ==================================*/

signed char __at(0x5C78) Timer_ticks;

void Timer_Until (void) __naked {
  __asm
loop$:
  LD   A,(_Timer_ticks) ; High byte
  AND  #0x80
  RET  Z
  HALT
  JR   loop$
  __endasm;
} //Timer_Until
