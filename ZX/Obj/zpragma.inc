// https://github.com/z88dk/z88dk/wiki/NewLib--Platform--Embedded

#pragma output CRT_ORG_CODE = 24100
#pragma output CRT_ORG_DATA = 23296
#pragma output CLIB_MALLOC_HEAP_SIZE = 0 // do not create a heap so that malloc() will not work
#pragma output CLIB_STDIO_HEAP_SIZE = 0  // cannot open files
#pragma output CLIB_EXIT_STACK_SIZE = 0  // no atexit() functions
#pragma output CLIB_FOPEN_MAX       = -1 // no FILE* list
#pragma output CLIB_OPEN_MAX        = -1 // no fd table
#pragma output REGISTER_SP = -1 // do not change the value of SP at startup
#pragma output CRT_ON_EXIT = 0x10002     // RETURN TO CALLER
#pragma output CRT_ENABLE_CLOSE     = 0  // don't bother closing files on exit
#pragma output CRT_ENABLE_EIDI = 0       // don't di on start or exit; loader does di before start