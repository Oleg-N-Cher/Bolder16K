/* Ofront+ 1.0 -m3 -48 */
#include "SYSTEM.oh"
#include "Console.oh"
#include "TapeTAP.oh"
#include "Files.oh"


static BYTE GenLoader_loader [1024];
static INTEGER GenLoader_loaderLen;
static BYTE GenLoader_code [41636];
static INTEGER GenLoader_codeLen;
static BYTE GenLoader_screen [6912];
static Files_FileToRead GenLoader_loaderFile, GenLoader_codeFile;
static TapeTAP_TapeFile GenLoader_tap;




/*============================================================================*/


int main(int argc, char **argv)
{
	__INIT(argc, argv);
	__IMPORT(Files__init);
	__IMPORT(Console__init);
	__IMPORT(TapeTAP__init);
	__REGMAIN("GenLoader", 0);
/* BEGIN */
	__Files_File_OpenToRead((void*)&GenLoader_loaderFile, Files_FileToRead__typ, (CHAR*)"..\\Bin\\BasicLoader.bas", 23);
	if (GenLoader_loaderFile.error || GenLoader_loaderFile.end) {
		Console_WriteStr((CHAR*)"Can\'t open file \'..\\Bin\\BasicLoader.bas\'.", 42);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -678);
	}
	GenLoader_loaderLen = 0;
	while (!(GenLoader_loaderFile.error || GenLoader_loaderFile.end)) {
		GenLoader_loader[__X(GenLoader_loaderLen, 1024, (CHAR*)"GenLoader", -800)] = __Files_FileToRead_ReadByte(&GenLoader_loaderFile, Files_FileToRead__typ);
		GenLoader_loaderLen += 1;
	}
	if (GenLoader_loaderFile.error) {
		__Files_File_Close((void*)&GenLoader_loaderFile, Files_FileToRead__typ);
		Console_WriteStr((CHAR*)"Can\'t read file \'..\\Bin\\BasicLoader.bas\'.", 42);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -959);
	}
	__Files_File_Close((void*)&GenLoader_loaderFile, Files_FileToRead__typ);
	GenLoader_loaderLen -= 1;
	__Files_File_OpenToRead((void*)&GenLoader_codeFile, Files_FileToRead__typ, (CHAR*)"..\\Bin\\Screen.bin", 18);
	if (GenLoader_codeFile.error || GenLoader_codeFile.end) {
		Console_WriteStr((CHAR*)"Can\'t open file \'Screen.bin\'.", 30);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -1381);
	}
	GenLoader_codeLen = 0;
	while (!(GenLoader_codeFile.error || GenLoader_codeFile.end)) {
		GenLoader_screen[__X(GenLoader_codeLen, 6912, (CHAR*)"GenLoader", -1493)] = __Files_FileToRead_ReadByte(&GenLoader_codeFile, Files_FileToRead__typ);
		GenLoader_codeLen += 1;
	}
	if (GenLoader_codeFile.error) {
		__Files_File_Close((void*)&GenLoader_codeFile, Files_FileToRead__typ);
		Console_WriteStr((CHAR*)"Can\'t read file \'Screen.bin\'.", 30);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -1630);
	}
	__Files_File_Close((void*)&GenLoader_codeFile, Files_FileToRead__typ);
	if (GenLoader_codeLen != 6912) {
		Console_WriteStr((CHAR*)"The file \'Screen.bin\' is not screen", 36);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -1756);
	}
	__Files_File_OpenToRead((void*)&GenLoader_codeFile, Files_FileToRead__typ, (CHAR*)"Bolder16K.bin", 14);
	if (GenLoader_codeFile.error || GenLoader_codeFile.end) {
		Console_WriteStr((CHAR*)"Can\'t open file \'Bolder16K.bin\'.", 33);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -1948);
	}
	GenLoader_codeLen = 0;
	while (!(GenLoader_codeFile.error || GenLoader_codeFile.end)) {
		GenLoader_code[__X(GenLoader_codeLen, 41636, (CHAR*)"GenLoader", -2058)] = __Files_FileToRead_ReadByte(&GenLoader_codeFile, Files_FileToRead__typ);
		GenLoader_codeLen += 1;
	}
	if (GenLoader_codeFile.error) {
		__Files_File_Close((void*)&GenLoader_codeFile, Files_FileToRead__typ);
		Console_WriteStr((CHAR*)"Can\'t read file \'Bolder16K.bin\'.", 33);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -2198);
	}
	__Files_File_Close((void*)&GenLoader_codeFile, Files_FileToRead__typ);
	__TapeTAP_TapeFile_ReCreate(&GenLoader_tap, TapeTAP_TapeFile__typ, (CHAR*)"..\\Bolder16K.tap", 17);
	if (GenLoader_tap.error) {
		Console_WriteStr((CHAR*)"Can\'t create tape file", 23);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -2365);
	}
	__TapeTAP_TapeFile_SaveBasic(&GenLoader_tap, TapeTAP_TapeFile__typ, (CHAR*)"Bolder16K", 10, 0, GenLoader_loaderLen, (void*)GenLoader_loader, 1024);
	__TapeTAP_TapeFile_SaveCode(&GenLoader_tap, TapeTAP_TapeFile__typ, (CHAR*)"Screen", 7, 16384, 6912, (void*)GenLoader_screen, 6912);
	__TapeTAP_TapeFile_SaveCode(&GenLoader_tap, TapeTAP_TapeFile__typ, (CHAR*)"Bolder16K", 10, 24100, GenLoader_codeLen, (void*)GenLoader_code, 41636);
	__TapeTAP_TapeFile_Finalize(&GenLoader_tap, TapeTAP_TapeFile__typ);
	if (GenLoader_tap.error) {
		Console_WriteStr((CHAR*)"Can\'t save tape file", 21);
		Console_WriteLn();
		__HALT(1, (CHAR*)"GenLoader", -2644);
	}
	__HALT(0, (CHAR*)"GenLoader", -2661);
	__FINI;
}
