/* Configuration file of the library Basic: */

/* Interrupt mode of your program: DI, IM1, IM2. */
/* For IM 1 mode use SDCC option --reserve-regs-iy */
#define MODE_DI
//#define MODE_IM1
//#define MODE_IM2

/* RND() result type: SHORTCARD (0..255) or CARDINAL (0..65535). */
//#define RND_SHORTCARD

/* Use ROM output (RST 10H, slow, 32x22) or CUSTOM (fast, 32x24) */
#define ROM_OUTPUT

/* Use fastcall model (the function parameters passed in regs.)  */

//#define BORDER_inline
//#define DRAW_fastcall
//#define PLOT_fastcall
//#define POINT_fastcall

/* Use CLS for whole screen (with PAPER attributes in bottom lines): */
//#define CLS_FULLSCREEN

