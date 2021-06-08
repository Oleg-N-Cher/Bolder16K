void Sound_Death (unsigned char y) __z88dk_fastcall;
void Sound_DropStoneOrAlmas (unsigned char y) __z88dk_fastcall;
void Sound_GetAlmas (unsigned int xn_plus_yn) __z88dk_fastcall;
void Sound_KeyPressed (void);
/*================================== Header ==================================*/

static void BEEPER (unsigned int de, unsigned int hl) __naked __z88dk_callee {
  __asm
    POP  BC
    POP  DE
    POP  HL
    PUSH BC
    PUSH IX
    CALL 0x3B5
    POP  IX
    RET
__endasm;
} //BEEPER

/*--------------------------------- Cut here ---------------------------------*/
void Sound_Death (unsigned char y) __z88dk_fastcall { //Terrible Sound Of Death
/*
  unsigned ctr = y << 2, lim = ctr + 16;
  for (;ctr < lim; ctr ++)
    snd (((ctr >> 3) | (ctr << 5)) & 0xFF, 8); //Terrible Sound Of Death
*/
unsigned char ctr, lim;
  ctr = y * 4; lim = ctr + 16;
  while (ctr < lim) {
  	unsigned int freq = ((ctr / 8) + (ctr * 32)) % 256;
    BEEPER(4, freq * 7 / 3);
    ctr++;
  }
} //Sound_Death

/*--------------------------------- Cut here ---------------------------------*/
void Sound_DropStoneOrAlmas (unsigned char y) __z88dk_fastcall {
/*
  snd (200 + (y << 1), 10);

  PC
  ==
  200 + 2*y = 2*(100 + y)
  SpkrPort = fr*6 = 6*2*(100 + y) = 12*(100 + y)
         1193181       99431,75
  Hz = ------------ = ---------
       12*(100 + y)    100 + y

  ZX
  ==
  HL = 437500 / Hz - 30.125 ~= 110.675
*/
  BEEPER(4, y*5 + 400);
} //Sound_DropStoneOrAlmas

/*--------------------------------- Cut here ---------------------------------*/
void Sound_GetAlmas (unsigned int xn_plus_yn) __z88dk_fastcall {
/*
  snd (60 + ((xn + yn) << 1), 8);
*/
  BEEPER(8, xn_plus_yn*13 / 3 + 103);
} //Sound_GetAlmas

/*--------------------------------- Cut here ---------------------------------*/
void Sound_KeyPressed (void) {
/*
  snd (64, 64);

  PC
  ==
  SpkrPort = fr * 6 = 64 * 6 = 384
  Hz = 1193181 / 384 = 3107.2421875
  
  ZX
  ==
  HL = 437500 / Hz - 30.125 ~= 110.675
*/
  BEEPER(50, 111);
} //Sound_KeyPressed
